/*****************************************************************************
 * threads.c : threads implementation for the VideoLAN client
 *****************************************************************************
 * Copyright (C) 1999-2008 the VideoLAN team
 * $Id: 265f60bd8bb922636cc36f47e6d34c710faf9d89 $
 *
 * Authors: Jean-Marc Dressler <polux@via.ecp.fr>
 *          Samuel Hocevar <sam@zoy.org>
 *          Gildas Bazin <gbazin@netcourrier.com>
 *          Clément Sténac
 *          Rémi Denis-Courmont
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_common.h>

#include "libvlc.h"
#include <assert.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#if defined( LIBVLC_USE_PTHREAD )
# include <sched.h>
#endif

#ifdef ANDROID
#include <sys/time.h>
#include <sys/resource.h>
#endif

struct vlc_thread_boot
{
    void * (*entry) (vlc_object_t *);
    vlc_object_t *object;
#ifdef ANDROID
    int priority;
#endif
};

static void *thread_entry (void *data)
{
    vlc_object_t *obj = ((struct vlc_thread_boot *)data)->object;
    void *(*func) (vlc_object_t *) = ((struct vlc_thread_boot *)data)->entry;
#ifdef ANDROID
    int priority = ((struct vlc_thread_boot *)data)->priority;
    priority = 19 - priority * (19 + 20) / (VLC_THREAD_PRIORITY_HIGHEST - VLC_THREAD_PRIORITY_LOW);
    setpriority(PRIO_PROCESS, 0, priority);
#endif

    free (data);
    msg_Dbg (obj, "thread started");
    func (obj);
    msg_Dbg (obj, "thread ended");

    return NULL;
}

#undef vlc_thread_create
/*****************************************************************************
 * vlc_thread_create: create a thread
 *****************************************************************************
 * Note that i_priority is only taken into account on platforms supporting
 * userland real-time priority threads.
 *****************************************************************************/
int vlc_thread_create( vlc_object_t *p_this, void *(*func) ( vlc_object_t * ),
                       int i_priority )
{
    int i_ret;
    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    struct vlc_thread_boot *boot = malloc (sizeof (*boot));
    if (boot == NULL)
        return errno;
    boot->entry = func;
    boot->object = p_this;
#ifdef ANDROID
    boot->priority = i_priority;
#endif

    /* Make sure we don't re-create a thread if the object has already one */
    assert( !p_priv->b_thread );

    i_ret = vlc_clone( &p_priv->thread_id, thread_entry, boot, i_priority );
    if( i_ret == 0 )
        p_priv->b_thread = true;
    else
    {
        errno = i_ret;
        msg_Err( p_this, "cannot create thread (%m)" );
        free (boot);
    }

    return i_ret;
}

#undef vlc_thread_set_priority
/*****************************************************************************
 * vlc_thread_set_priority: set the priority of the current thread when we
 * couldn't set it in vlc_thread_create (for instance for the main thread)
 *****************************************************************************/
int vlc_thread_set_priority( vlc_object_t *p_this, int i_priority )
{
    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    if( !p_priv->b_thread )
    {
        msg_Err( p_this, "couldn't set priority of non-existent thread" );
        return ESRCH;
    }

#if defined( LIBVLC_USE_PTHREAD )
# ifndef __APPLE__
    if( var_InheritBool( p_this, "rt-priority" ) )
# endif
    {
        int i_error, i_policy;
        struct sched_param param;

        memset( &param, 0, sizeof(struct sched_param) );
        if( config_GetType( p_this, "rt-offset" ) )
            i_priority += var_InheritInteger( p_this, "rt-offset" );
        if( i_priority <= 0 )
        {
            param.sched_priority = (-1) * i_priority;
            i_policy = SCHED_OTHER;
        }
        else
        {
            param.sched_priority = i_priority;
            i_policy = SCHED_RR;
        }
        if( (i_error = pthread_setschedparam( p_priv->thread_id,
                                              i_policy, &param )) )
        {
            errno = i_error;
            msg_Warn( p_this, "cannot set thread priority (%m)" );
            i_priority = 0;
        }
    }

#elif defined( WIN32 ) || defined( UNDER_CE )

#warning vlc_thread_set_priority() is BROKEN
    if( true /*!SetThreadPriority(p_priv->thread_id->id, i_priority)*/ )
    {
        msg_Warn( p_this, "couldn't set a faster priority" );
        return 1;
    }

#endif

    return 0;
}

#undef vlc_thread_join
/*****************************************************************************
 * vlc_thread_join: wait until a thread exits, inner version
 *****************************************************************************/
void vlc_thread_join( vlc_object_t *p_this )
{
    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    vlc_join( p_priv->thread_id, NULL );
    p_priv->b_thread = false;
}

void vlc_thread_cancel (vlc_object_t *obj)
{
    vlc_object_internals_t *priv = vlc_internals (obj);

    if (priv->b_thread)
        vlc_cancel (priv->thread_id);
}

/*** Global locks ***/

void vlc_global_mutex (unsigned n, bool acquire)
{
    static vlc_mutex_t locks[] = {
        VLC_STATIC_MUTEX,
        VLC_STATIC_MUTEX,
        VLC_STATIC_MUTEX,
    };
    assert (n < (sizeof (locks) / sizeof (locks[0])));
    vlc_mutex_t *lock = locks + n;

    if (acquire)
        vlc_mutex_lock (lock);
    else
        vlc_mutex_unlock (lock);

    /* Compile-time assertion ;-) */
    char enough_locks[(sizeof (locks) / sizeof (locks[0])) - VLC_MAX_MUTEX];
    (void) enough_locks;
}

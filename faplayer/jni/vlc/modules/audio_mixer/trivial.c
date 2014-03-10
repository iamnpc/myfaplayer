/*****************************************************************************
 * trivial.c : trivial mixer plug-in (1 input, no downmixing)
 *****************************************************************************
 * Copyright (C) 2002 the VideoLAN team
 * $Id: 09437102eb5615a2545bdd9b03a2b10a22d4506f $
 *
 * Authors: Christophe Massiot <massiot@via.ecp.fr>
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

/*****************************************************************************
 * Preamble
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stddef.h>
#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_aout.h>

/*****************************************************************************
 * Local prototypes
 *****************************************************************************/
static int  Create    ( vlc_object_t * );

static void DoWork    ( aout_mixer_t *, aout_buffer_t * );

/*****************************************************************************
 * Module descriptor
 *****************************************************************************/
vlc_module_begin ()
    set_category( CAT_AUDIO )
    set_subcategory( SUBCAT_AUDIO_MISC )
    set_description( N_("Trivial audio mixer") )
    set_capability( "audio mixer", 1 )
    set_callbacks( Create, NULL )
vlc_module_end ()

/*****************************************************************************
 * Create: allocate trivial mixer
 *****************************************************************************/
static int Create( vlc_object_t *p_this )
{
    aout_mixer_t *p_mixer = (aout_mixer_t *)p_this;

    if ( p_mixer->fmt.i_format != VLC_CODEC_FL32
          && p_mixer->fmt.i_format != VLC_CODEC_FI32 )
    {
        return -1;
    }

    p_mixer->mix = DoWork;

    return 0;
}

/*****************************************************************************
 * DoWork: mix a new output buffer
 *****************************************************************************/
static void DoWork( aout_mixer_t *p_mixer, aout_buffer_t * p_buffer )
{
    aout_mixer_input_t *p_input = p_mixer->input;
    int i_nb_channels = aout_FormatNbChannels( &p_mixer->fmt );
    int i_buffer = p_buffer->i_nb_samples * sizeof(int32_t)
                      * i_nb_channels;
    uint8_t * p_in;
    uint8_t * p_out;

    p_in = p_input->begin;
    p_out = p_buffer->p_buffer;

    for ( ; ; )
    {
        ptrdiff_t i_available_bytes = (p_input->fifo.p_first->p_buffer
                                        - p_in)
                                        + p_input->fifo.p_first->i_nb_samples
                                           * sizeof(int32_t)
                                           * i_nb_channels;

        if ( i_available_bytes < i_buffer )
        {
            aout_buffer_t * p_old_buffer;

            vlc_memcpy( p_out, p_in, i_available_bytes );
            i_buffer -= i_available_bytes;
            p_out += i_available_bytes;

            /* Next buffer */
            p_old_buffer = aout_FifoPop( NULL, &p_input->fifo );
            aout_BufferFree( p_old_buffer );
            if ( p_input->fifo.p_first == NULL )
            {
                msg_Err( p_mixer, "internal amix error" );
                return;
            }
            p_in = p_input->fifo.p_first->p_buffer;
        }
        else
        {
            vlc_memcpy( p_out, p_in, i_buffer );
            p_input->begin = p_in + i_buffer;
            break;
        }
    }
}

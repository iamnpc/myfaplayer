/**
 * @file dtv.h
 * @brief Digital TV module common header
 */
/*****************************************************************************
 * Copyright © 2011 Rémi Denis-Courmont
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/

#ifndef VLC_DTV_H
# define VLC_DTV_H 1
# ifdef __cplusplus
extern "C" {
# endif

typedef struct delsys delsys_t;

extern const delsys_t dvbc, dvbs, dvbs2, dvbt, atsc, cqam;

typedef struct dvb_device dvb_device_t;

dvb_device_t *dvb_open (vlc_object_t *obj, bool tune);
void dvb_close (dvb_device_t *);
ssize_t dvb_read (dvb_device_t *, void *, size_t);

int dvb_add_pid (dvb_device_t *, uint16_t);
void dvb_remove_pid (dvb_device_t *, uint16_t);

const delsys_t *dvb_guess_system (dvb_device_t *);
float dvb_get_signal_strength (dvb_device_t *);
float dvb_get_snr (dvb_device_t *);

int dvb_set_inversion (dvb_device_t *, int);
int dvb_tune (dvb_device_t *);

#define VLC_FEC(a,b)   (((a) << 16u) | (b))
#define VLC_FEC_AUTO   0xFFFFFFFF
#define VLC_GUARD(a,b) (((a) << 16u) | (b))
#define VLC_GUARD_AUTO 0xFFFFFFFF

/* DVB-C */
int dvb_set_dvbc (dvb_device_t *, uint32_t freq, const char *mod,
                  uint32_t srate, uint32_t fec);

/* DVB-S */
int dvb_set_dvbs (dvb_device_t *, uint32_t freq, uint32_t srate, uint32_t fec);
int dvb_set_dvbs2 (dvb_device_t *, uint32_t freq, const char *mod,
                   uint32_t srate, uint32_t fec, int pilot, int rolloff);
int dvb_set_sec (dvb_device_t *, uint32_t freq, char pol,
                 uint32_t lowf, uint32_t highf, uint32_t switchf);

/* DVB-T */
int dvb_set_dvbt (dvb_device_t *, uint32_t freq, const char *mod,
                  uint32_t fec_hp, uint32_t fec_lp, uint32_t bandwidth,
                  int transmission, uint32_t guard, int hierarchy);

/* ATSC */
int dvb_set_atsc (dvb_device_t *, uint32_t freq, const char *mod);
int dvb_set_cqam (dvb_device_t *, uint32_t freq, const char *mod);

/* ISDB-T */
typedef struct isdbt_layer
{
    const char *modulation;
    const char *code_rate;
    uint8_t segment_count;
    uint8_t time_interleaving;
} isdbt_layer_t;

typedef struct isdbt_sound
{
    uint8_t subchannel_id;
    uint8_t segment_index;    uint8_t segment_cound;
} isdbt_sound_t;

int dvb_set_isdbt (dvb_device_t *, uint32_t freq, const isdbt_layer_t *a,
                   const isdbt_layer_t *b, const isdbt_layer_t *c,
                   const isdbt_sound_t *sb);
# ifdef __cplusplus
}
# endif
#endif

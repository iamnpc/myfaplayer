
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
ifeq ($(BUILD_WITH_NEON),1)
LOCAL_ARM_NEON := true
endif

LOCAL_MODULE := vlccore

LOCAL_CFLAGS += \
    -DICONV_CONST=

LOCAL_CFLAGS += \
    -std=c99 \
    -DHAVE_CONFIG_H \
    -DMODULE_STRING=\"main\" \
    -DPACKAGENAME=\"org.stagex.danmaku\" \
    -DLOCALEDIR=\"/data/data/\"PACKAGENAME\"/cache/locale\" \
    -DSYSCONFDIR=\"/data/data/\"PACKAGENAME\"/cache/etc\" \
    -DDATA_PATH=\"/data/data/\"PACKAGENAME\"/cache/share\" \
    -DPKGLIBDIR=\"/data/data/\"PACKAGENAME\"/cache/lib\"

LOCAL_C_INCLUDES += \
    $(EXTROOT)/iconv/include

LOCAL_C_INCLUDES += \
    $(VLCROOT) \
    $(VLCROOT)/include \
    $(VLCROOT)/src

LOCAL_SRC_FILES := \
    src/libvlc-module.c \
    src/libvlc.c \
    src/libvlcjni.c \
    src/missing.c \
    src/revision.c \
    src/version.c \
    src/audio_output/common.c \
    src/audio_output/dec.c \
    src/audio_output/filters.c \
    src/audio_output/input.c \
    src/audio_output/intf.c \
    src/audio_output/mixer.c \
    src/audio_output/output.c \
    src/config/chain.c \
    src/config/cmdline.c \
    src/config/core.c \
    src/config/dirs.c \
    src/config/file.c \
    src/config/getopt.c \
    src/config/intf.c \
    src/config/keys.c \
    src/control/audio.c \
    src/control/core.c \
    src/control/error.c \
    src/control/event.c \
    src/control/event_async.c \
    src/control/log.c \
    src/control/media.c \
    src/control/media_discoverer.c \
    src/control/media_library.c \
    src/control/media_list.c \
    src/control/media_list_player.c \
    src/control/media_player.c \
    src/control/playlist.c \
    src/control/video.c \
    src/extras/libc.c \
    src/extras/tdestroy.c \
    src/input/access.c \
    src/input/clock.c \
    src/input/control.c \
    src/input/decoder.c \
    src/input/decoder_synchro.c \
    src/input/demux.c \
    src/input/es_out.c \
    src/input/es_out_timeshift.c \
    src/input/event.c \
    src/input/input.c \
    src/input/item.c \
    src/input/meta.c \
    src/input/resource.c \
    src/input/stream.c \
    src/input/stream_demux.c \
    src/input/stream_filter.c \
    src/input/stream_memory.c \
    src/input/subtitles.c \
    src/input/var.c \
    src/interface/dialog.c \
    src/interface/interface.c \
    src/interface/intf_eject.c \
    src/misc/atomic.c \
    src/misc/block.c \
    src/misc/cpu.c \
    src/misc/epg.c \
    src/misc/error.c \
    src/misc/es_format.c \
    src/misc/events.c \
    src/misc/exit.c \
    src/misc/filter.c \
    src/misc/filter_chain.c \
    src/misc/fourcc.c \
    src/misc/http_auth.c \
    src/misc/image.c \
    src/misc/md5.c \
    src/misc/media_library.c \
    src/misc/messages.c \
    src/misc/mtime.c \
    src/misc/objects.c \
    src/misc/picture.c \
    src/misc/picture_fifo.c \
    src/misc/picture_pool.c \
    src/misc/probe.c \
    src/misc/rand.c \
    src/misc/sql.c \
    src/misc/stats.c \
    src/misc/subpicture.c \
    src/misc/text_style.c \
    src/misc/threads.c \
    src/misc/update.c \
    src/misc/update_crypto.c \
    src/misc/variables.c \
    src/misc/xml.c \
    src/modules/cache.c \
    src/modules/entry.c \
    src/modules/modules.c \
    src/modules/os.c \
    src/modules/textdomain.c \
    src/network/acl.c \
    src/network/getaddrinfo.c \
    src/network/io.c \
    src/network/poll.c \
    src/network/rootbind.c \
    src/network/tcp.c \
    src/network/tls.c \
    src/network/udp.c \
    src/osd/osd.c \
    src/osd/osd_text.c \
    src/playlist/art.c \
    src/playlist/control.c \
    src/playlist/engine.c \
    src/playlist/fetcher.c \
    src/playlist/item.c \
    src/playlist/loadsave.c \
    src/playlist/preparser.c \
    src/playlist/search.c \
    src/playlist/services_discovery.c \
    src/playlist/sort.c \
    src/playlist/thread.c \
    src/playlist/tree.c \
    src/posix/dirs.c \
    src/posix/filesystem.c \
    src/posix/linux_specific.c \
    src/posix/thread.c \
    src/text/charset.c \
    src/text/filesystem.c \
    src/text/iso_lang.c \
    src/text/strings.c \
    src/text/unicode.c \
    src/video_output/control.c \
    src/video_output/display.c \
    src/video_output/inhibit.c \
    src/video_output/interlacing.c \
    src/video_output/opengl.c \
    src/video_output/postprocessing.c \
    src/video_output/snapshot.c \
    src/video_output/video_epg.c \
    src/video_output/video_output.c \
    src/video_output/video_text.c \
    src/video_output/video_widgets.c \
    src/video_output/vout_intf.c \
    src/video_output/vout_subpictures.c \
    src/video_output/vout_wrapper.c \
    src/video_output/window.c

LOCAL_LDLIBS += -ldl -llog -lz

# modules begin
LOCAL_STATIC_LIBRARIES += access_http_plugin access_mms_plugin aout_android_plugin audio_format_neon_plugin avcodec_plugin avformat_plugin bandlimited_resampler_plugin blend_plugin converter_fixed_plugin dummy_plugin filesystem_plugin float32_mixer_plugin freetype_plugin libasf_plugin libass_plugin libavi_plugin libmp4_plugin live555_plugin mpgv_plugin packetizer_copy_plugin packetizer_dirac_plugin packetizer_flac_plugin packetizer_h264_plugin packetizer_mlp_plugin packetizer_mpeg4audio_plugin packetizer_mpeg4video_plugin packetizer_mpegvideo_plugin packetizer_vc1_plugin realrtsp_plugin reporter_plugin simple_channel_mixer_plugin subsdec_plugin subsusf_plugin subtitle_plugin swscale_plugin trivial_mixer_plugin ugly_resampler_plugin vout_android_plugin yuv2rgb_plugin
# modules end

LOCAL_STATIC_LIBRARIES += compat

ifeq ($(BUILD_WITH_NEON),1)
LOCAL_STATIC_LIBRARIES += arm_neon
endif

LOCAL_STATIC_LIBRARIES += ass freetype iconv charset live555 pixman

LOCAL_WHOLE_STATIC_LIBRARIES += avformat avfilter avcodec avdevice avutil swscale

include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))


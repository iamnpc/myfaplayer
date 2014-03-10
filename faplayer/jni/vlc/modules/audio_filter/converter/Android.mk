
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
ifeq ($(BUILD_WITH_NEON),1)
LOCAL_ARM_NEON := true
endif

LOCAL_MODULE := converter_fixed_plugin

LOCAL_CFLAGS += \
    -std=c99 \
    -DHAVE_CONFIG_H \
    -DMODULE_STRING=\"converter_fixed\" \
    -DMODULE_NAME=converter_fixed

LOCAL_C_INCLUDES += \
    $(VLCROOT) \
    $(VLCROOT)/include \
    $(VLCROOT)/src

LOCAL_SRC_FILES := \
    fixed.c

include $(BUILD_STATIC_LIBRARY)


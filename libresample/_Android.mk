LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# LOCAL_PRELINK_MODULE := false

LOCAL_SHARED_LIBRARIES :=

LOCAL_STATIC_LIBRARIES :=

LOCAL_C_INCLUDES :=

LOCAL_CFLAGS :=

LOCAL_SRC_FILES := \
	resample.c \
	resample2.c

LOCAL_LDFLAGS +=

LOCAL_MODULE := libresample

LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)

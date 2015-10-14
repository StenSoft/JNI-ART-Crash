LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := crash
LOCAL_SRC_FILES := crash.cc

include $(BUILD_SHARED_LIBRARY)

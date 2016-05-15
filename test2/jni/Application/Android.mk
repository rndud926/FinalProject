LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE			:=	test2
LOCAL_SRC_FILES			:=	test2.c UHclientmain.c UHffmpeg.c UHsurfaceview.c UHringbuffer.c
LOCAL_C_INCLUDES		:=	$(LOCAL_PATH)/../FFmpeg				\
							$(LOCAL_PATH)/../FFmpeg/libavcodec	\
							$(LOCAL_PATH)/../FFmpeg/libavformat	\
							$(LOCAL_PATH)/../FFmpeg/libavutil	\
							$(LOCAL_PATH)/../FFmpeg/libswscale
LOCAL_STATIC_LIBRARIES	:=	libavformat libavcodec libswscale libavutil
LOCAL_LDLIBS			:=	-lz -llog -lGLESv1_CM
LOCAL_ARM_MODE			:=	arm

include $(BUILD_SHARED_LIBRARY)
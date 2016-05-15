#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include "test2.h"
#include "UHsurfaceview.h"

JNIEXPORT jint JNICALL Java_com_example_test2_MainActivity_Init(JNIEnv *env, jclass jcls, jstring _ip)
{
	int errno = 0;
	__android_log_print(ANDROID_LOG_DEBUG, "NativeInit",  "1111111111111111111111");
	const char *ip = (*env)->GetStringUTFChars(env,_ip,0);
	int rev = sockInit(ip);
	if( rev == -1)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "Init", "Connect Error!\n");
		return -1;
	}

	return 1;
}

JNIEXPORT void JNICALL Java_com_example_test2_MainActivity_CreatedGlView(JNIEnv *env, jclass jcls)
{
	OnSurfaceCreated();
}

JNIEXPORT void JNICALL Java_com_example_test2_MainActivity_UpdateGlView(JNIEnv *env, jclass jcls)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	DrawFrameRGB24();
}

JNIEXPORT void JNICALL Java_com_example_test2_MainActivity_ChangedGlView(JNIEnv *env, jclass jcls, jint width, jint height)
{
	OnSurfaceChanged(width, height);
}


/*
 * test2.h
 *
 *  Created on: 2014. 6. 9.
 *      Author: j_
 */

#ifndef TEST2_H_
#define TEST2_H_

#include <jni.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#ifdef __CPLUSPLUS
extern "C"
{
#endif

JNIEXPORT jint JNICALL Java_com_example_test2_MainActivity_add(JNIEnv* env,jobject thiz, jint a, jint b);

JNIEXPORT jint JNICALL Java_com_example_test2_MainActivity_sub(JNIEnv* env,jobject thiz, jint a, jint b);

JNIEXPORT jint JNICALL Java_com_example_test2_MainActivity_mul(JNIEnv* env,jobject thiz, jint a, jint b);

JNIEXPORT jint JNICALL Java_com_example_test2_MainActivity_div(JNIEnv* env,jobject thiz, jint a, jint b);

JNIEXPORT jint JNICALL Java_com_example_nativetest_Native_Init(JNIEnv *env, jclass jcls, jstring b);

JNIEXPORT void JNICALL Java_com_example_test2_MainActivity_CreatedGlView(JNIEnv *env, jclass jcls);

JNIEXPORT void JNICALL Java_com_example_test2_MainActivity_UpdateGlView(JNIEnv *env, jclass jcls);

JNIEXPORT void JNICALL Java_com_example_test2_MainActivity_ChangedGlView(JNIEnv *env, jclass jcls, jint width, jint height);

#ifdef __CPLUSPLUS
}
#endif

#endif /* TEST2_H_ */

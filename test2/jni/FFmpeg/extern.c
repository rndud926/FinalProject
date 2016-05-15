#include <android/log.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avcodec.h"
#include "swscale.h"

AVCodecContext *pCodecContext;
AVCodec *pCodec;
AVFrame *pFrame;
AVFrame *pFrameRGB;
AVPacket mPacket;
struct SwsContext *pImgConvertCtx;

extern void decoder_1init()
{
	avcodec_init();
	avcodec_register_all();
}

extern int decoder_1open()
{
	pCodecContext = avcodec_alloc_context();
	pCodec = avcodec_find_decoder(CODEC_ID_H264);

	if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
		pCodecContext->flags |= CODEC_FLAG_TRUNCATED;

	if(avcodec_open(pCodecContext, pCodec) < 0)
		return -1;

	// 패킷 초기화
	// 프레임 초기화
	av_init_packet(&mPacket);
	pFrame = avcodec_alloc_frame();
	pFrameRGB = avcodec_alloc_frame();
	return 0;
}

extern int decoder_1close()
{
	if(pCodecContext)
		avcodec_close(pCodecContext);
	av_free(pCodecContext);
	
	// 패킷 릴리즈
	// 프레임 릴리즈
	av_free(pFrame);
	av_free(pFrameRGB);
	return 0;
}

extern int decoder_1decode(unsigned char* _inBuf, int inBufLen, unsigned char* outBuf)
{
	int retLen, got_picture = 0;

	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 1");
	
	mPacket.data = _inBuf;
	mPacket.size = inBufLen;

	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 2");

	retLen = avcodec_decode_video2(pCodecContext, pFrame, &got_picture, &mPacket);

	if(got_picture)
		__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 3 - success, %d", mPacket.size);
	else
		__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 3 - fail");

	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 4");

	return retLen;
}


extern int decoder_1render(unsigned char* _inBuf, int inBufLen, int width, int height, jobject bitmap)
{
	void *pixels;
	int retLen, result, got_picture = 0;

	mPacket.data = _inBuf;
	mPacket.size = inBufLen;

	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 1");

	retLen = avcodec_decode_video2(pCodecContext, pFrame, &got_picture, &mPacket);

	if(got_picture)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 2 - success, %d", mPacket.size);
	
		//pImgConvertCtx = sws_getCachedContext(pImgConvertCtx,
		//	pCodecContext->width, pCodecContext->height, pCodecContext->pix_fmt,
		//	pCodecContext->width, pCodecContext->height, PIX_FMT_RGB565LE, SWS_BICUBIC, NULL, NULL, NULL);
		pImgConvertCtx = sws_getCachedContext(pImgConvertCtx,
			width, height, pCodecContext->pix_fmt,
			width, height, PIX_FMT_RGB565LE, SWS_BICUBIC, NULL, NULL, NULL);
		__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni pCodecContext->pix_fmt : %d", pCodecContext->pix_fmt);

		sws_scale(pImgConvertCtx, pFrame->data, pFrame->linesize, 0, height, pFrameRGB->data, pFrameRGB->linesize);
	}
	else
		__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 2 - fail");

	(*env)->ReleaseByteArrayElements(env, inBuf, (jbyte*) _inBuf, JNI_ABORT);

	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 3");

	if ((result = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0)
		return result;
	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 4, result %d", result);
	memcpy(pixels, pFrameRGB->data[0], width*height*2);
	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 5");
	AndroidBitmap_unlockPixels(env, bitmap);
	__android_log_print(ANDROID_LOG_DEBUG, "kkpidentity", "jni 6");

	return retLen;
}
/*
 * UHffmpeg.c
 *
 *  Created on: 2014. 6. 9.
 *      Author: Admin
 */

#include "UHffmpeg.h"

//ffmpeg
AVCodecContext *pCodecCtx;
AVFrame *pVFrame;
AVFrame *pFrameRGB;
AVCodec *pCodec;
unsigned char *buffer;
int img_size;
struct SwsContext *img_convert_ctx;
int ffmpegInit()
{
	__android_log_print(ANDROID_LOG_DEBUG, "ffmpegInit", "Start");
	avcodec_init();
	av_register_all();
	pCodec = avcodec_find_decoder(CODEC_ID_H264);
	pCodecCtx = avcodec_alloc_context3(pCodec);

	pCodecCtx->width = IMAGE_WIDTH;
	pCodecCtx->height = IMAGE_HEIGHT;
	pCodecCtx->codec_id = CODEC_ID_H264;
	pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
	pCodecCtx->flags2 |= CODEC_FLAG2_FAST;
	pCodecCtx->thread_count = 0;
	pCodecCtx->pix_fmt = PIX_FMT_YUV420P;

	if(avcodec_open2(pCodecCtx, pCodec, 0) < 0)
		return -1;

	pVFrame = avcodec_alloc_frame(); // 디코딩 된 데이터를 담는 프레임 버퍼 할당
	pFrameRGB = avcodec_alloc_frame();

	img_size = avpicture_get_size(PIX_FMT_RGB24,IMAGE_WIDTH, IMAGE_HEIGHT);
	buffer = (unsigned char *) malloc(sizeof(unsigned char) * img_size);
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

	img_convert_ctx = sws_getCachedContext(img_convert_ctx,
		pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);


	return 1;
}


int ffmpegDecoding(unsigned char *sock_buffer, int ImageLength, int count, unsigned char *outputRGB)
{
	AVPacket packet;
	av_init_packet(&packet);

	//__android_log_print(ANDROID_LOG_DEBUG, "ffmpegDecoding", "Start");

	int bGotPicture = 0;

	packet.data = sock_buffer;
	packet.size = ImageLength;

	int len;
	__android_log_print(ANDROID_LOG_DEBUG, "FFmpegDecoing","Start");

	if( ( len = avcodec_decode_video2( pCodecCtx, pVFrame, &bGotPicture, &packet )) < 0)
		return -1;

	__android_log_print(ANDROID_LOG_DEBUG, "FFmpegDecoing","Len : %d",len);
	__android_log_print(ANDROID_LOG_DEBUG, "FFmpegDecoing","bGotPicture : %d",bGotPicture);
	__android_log_print(ANDROID_LOG_DEBUG, "FFmpegDecoing","End");

	if(bGotPicture)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "ColorConvert", "Start");

		sws_scale(img_convert_ctx, pVFrame->data, pVFrame->linesize, 0,pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
		memcpy(outputRGB, pFrameRGB->data[0], img_size);

		__android_log_print(ANDROID_LOG_DEBUG, "ColorConvert", "End");
	}

	av_free_packet(&packet);
	return 1;
}

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
  FILE *pFile;
  char szFilename[50];
  int  y;
  // Open file
  sprintf(szFilename, "/storage/emulated/0/testfile/frame%d.ppm", iFrame);
	__android_log_print(ANDROID_LOG_DEBUG, "SaveFrame", "%s",szFilename);

  pFile=fopen(szFilename, "wb");
  if(pFile==NULL)
  {
	__android_log_print(ANDROID_LOG_DEBUG, "SaveFrame", "FileOPenFail");
	  return;
  }
  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);

  // Write pixel data
  for(y=0; y<height; y++)
    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

  // Close file
  fclose(pFile);
}

int FFMpeg_Uninit()
{
	if(pCodecCtx)
		avcodec_close(pCodecCtx);
	av_free(pCodecCtx);

	av_free(pVFrame);
	av_free(pFrameRGB);
	return 0;
}



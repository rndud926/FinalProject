/*
 * UHmmfpeg.h
 *
 *  Created on: 2014. 6. 9.
 *      Author: Admin
 */

#ifndef UHMMFPEG_H_
#define UHMMFPEG_H_

#include <android/log.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avio.h>

#define IMAGE_WIDTH 960
#define IMAGE_HEIGHT 540

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);
int ffmpegDecoding(unsigned char *sock_buffer, int ImageLength, int count, unsigned char *output);
int ffmpegInit();
int FFMpeg_Uninit();

#endif /* UHMMFPEG_H_ */

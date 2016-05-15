/*
 * Init.h
 *
 *  Created on: 2014. 6. 9.
 *      Author: Admin
 */

#ifndef INIT_H_
#define INIT_H_

#include <android/log.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define WIDTH 960
#define HEIGHT 540

void * thread_video_decoding();
int UnInit();
int sockInit(const char *ip);
int ffmpegStart();

#endif /* INIT_H_ */

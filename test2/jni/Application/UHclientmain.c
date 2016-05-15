/*
 * Test.cpp
 *
 *  Created on: 2014. 6. 8.
 *      Author: Admin
 */

#include "UHclientmain.h"
#include "UHffmpeg.h"
#include "UHringbuffer.h"

pthread_t thread_id_a, thread_id_b, thread_id_c;
//sock
char IPADDRESS[30];
char sock_buffer[1024*1024];
int sock_control;
int start = 0;
unsigned char outputRGB[HEIGHT*WIDTH*3];

int sockInit(const char *ip)
{
	__android_log_print(ANDROID_LOG_DEBUG, "sockInit", "start");
	__android_log_print(ANDROID_LOG_DEBUG, "sockInit", "ip : %s",ip);

	struct sockaddr_in serv_addr_conn;

	sock_control = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_control == -1)
		return -1;

	memset(&serv_addr_conn, 0, sizeof(serv_addr_conn));
	serv_addr_conn.sin_family = AF_INET;
	serv_addr_conn.sin_addr.s_addr = inet_addr(ip);
	serv_addr_conn.sin_port = htons(8001);

	if(connect(sock_control, (struct sockaddr *) &serv_addr_conn, sizeof(serv_addr_conn)) == -1)
				return -1;

	strcpy(IPADDRESS, ip);
	__android_log_print(ANDROID_LOG_DEBUG, "sockInit", "end");

	ThreadCreate();

	return 0;
}

int UnInit()
{
	char endmessage[128] = "end";
	start = 0;
	pthread_join(thread_id_c, NULL);
	close(sock_control);
	return 0;
}

int ThreadCreate()
{
	//pthread_create(&thread_id_a, NULL, thread_video_receive, NULL);
	//pthread_create(&thread_id_b, NULL, thread_video_decode, NULL);
	pthread_create(&thread_id_c, NULL, thread_video_decoding, NULL);
	start = 1;
	return 0;
}

void *thread_video_decoding(void *arg)
{
	__android_log_print(ANDROID_LOG_DEBUG, "thread",  "thread decoding start");
	ffmpegInit();
	int test_stream = 1;
	int dataSize;
	int count = 0;
	while(start)
	{
		while(1)
		{
			//크기를 전송받음
			read(sock_control, &dataSize , 4);
			__android_log_print(ANDROID_LOG_DEBUG, "Init", "data size : %d count : %d ",dataSize, count);
			break;
		}

		int readSize = 0;

		while( readSize < dataSize)
		{
			readSize += read(sock_control, sock_buffer + readSize, dataSize - readSize);
		}

		ffmpegDecoding(sock_buffer,dataSize,count,outputRGB);
		count++;
	}

	UnInit();

	return NULL;
}

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <pthread.h>

#define RING_BUFFER_DATA_SIZE		960*540
#define RING_BUFFER_EXTRA_DATA_SIZE	960*540


typedef struct RingBuffer
{
	pthread_mutex_t mutex;

	unsigned char data[RING_BUFFER_DATA_SIZE + RING_BUFFER_EXTRA_DATA_SIZE];
	unsigned char *read_position;
	unsigned char *write_position;
	unsigned char *tail_position;

} RingBuffer;

RingBuffer *RingBuffer_Create();
void RingBuffer_Destroy(RingBuffer *rb);

int RingBuffer_GetUsedSize(RingBuffer *rb);
int RingBuffer_GetRemainSize(RingBuffer *rb);

int RingBuffer_GetRead(RingBuffer *rb, unsigned char **pdata, int size);
int RingBuffer_ReleaseRead(RingBuffer *rb, int size);
int RingBuffer_GetWrite(RingBuffer *rb, unsigned char **pdata, int size);
int RingBuffer_ReleaseWrite(RingBuffer *rb, int size);

#endif

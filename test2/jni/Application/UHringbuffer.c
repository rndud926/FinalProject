#include "UHringbuffer.h"

RingBuffer *RingBuffer_Create()
{
	RingBuffer *rb = (RingBuffer *) malloc(sizeof(RingBuffer));

	pthread_mutex_init(&rb->mutex, NULL);

	memset(rb->data, 0, RING_BUFFER_DATA_SIZE + RING_BUFFER_EXTRA_DATA_SIZE);
	rb->read_position = rb->data;
	rb->write_position = rb->data;
	rb->tail_position = rb->data + RING_BUFFER_DATA_SIZE;

	return rb;
}

void RingBuffer_Destroy(RingBuffer *rb)
{
	pthread_mutex_destroy(&rb->mutex);
	free(rb);
}

int RingBuffer_GetUsedSize(RingBuffer *rb)
{
	int size = (int) (rb->write_position - rb->read_position);
	if(size < 0)
		size += (rb->tail_position - rb->data);
	return size;
}

int RingBuffer_GetRemainSize(RingBuffer *rb)
{
	int size = (int) (rb->read_position - rb->write_position);
	if(size <= 0)
		size += RING_BUFFER_DATA_SIZE;
	return size;
}

int RingBuffer_GetRead(RingBuffer *rb, unsigned char **pdata, int size)
{
	int rtv;

	pthread_mutex_lock(&rb->mutex);

	if( size <= RingBuffer_GetUsedSize(rb) )
	{
		*pdata = rb->read_position;
		rtv = 0;
	}

	else
	{
		pdata = NULL;
		rtv = -1;
	}

	pthread_mutex_unlock(&rb->mutex);

	return rtv;
}

int RingBuffer_ReleaseRead(RingBuffer *rb, int size)
{
	pthread_mutex_lock(&rb->mutex);

	rb->read_position += size;
	if( (rb->data + RING_BUFFER_DATA_SIZE) <= rb->read_position )
	{
		rb->tail_position = rb->data + RING_BUFFER_DATA_SIZE;
		rb->read_position = rb->data;
	}

	pthread_mutex_unlock(&rb->mutex);

	return 0;
}

int RingBuffer_GetWrite(RingBuffer *rb, unsigned char **pdata, int size)
{
	int rtv;

	pthread_mutex_lock(&rb->mutex);

	if( size < RingBuffer_GetRemainSize(rb) )
	{
		*pdata = rb->write_position;
		rtv = 0;
	}

	else
	{
		*pdata = NULL;
		rtv = -1;
	}

	pthread_mutex_unlock(&rb->mutex);

	return rtv;
}

int RingBuffer_ReleaseWrite(RingBuffer *rb, int size)
{
	pthread_mutex_lock(&rb->mutex);

	rb->write_position += size;
	if( (rb->data + RING_BUFFER_DATA_SIZE) <= rb->write_position )
	{
		rb->tail_position = rb->write_position;
		rb->write_position = rb->data;
	}

	pthread_mutex_unlock(&rb->mutex);

	return 0;
}

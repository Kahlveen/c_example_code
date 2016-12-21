#include "ring_buffer.h"

/*
 * Return 0 if success, -1 if cannot allocate memory
 */
int ringbuf_init(ring_buffer_t* rb, size_t capacity, size_t sz)
{
	rb->buffer = malloc(capacity * sz);
	if(rb->buffer == NULL)
		return -1;

	rb->buffer_end = (char*)rb->buffer + capacity*sz;
	rb->capacity = capacity;
	rb->count = 0;
	rb->sz = sz;
	rb->head = rb->buffer;
	rb->tail = rb->buffer;
	return 0;
}

void ringbuf_free(ring_buffer_t* rb)
{
	free(rb->buffer);
}

/*
 *	Returns 0 if nothing is overwritten,
 *	-1 if item is overwritten.
 */
int ringbuf_pushback(ring_buffer_t* rb, const void* item)
{
	int retval = 0;
	if (rb->count == rb->capacity){	
		retval = -1;
		rb->count--;
	}

	memcpy(rb->head, item, rb->sz);
	rb->head = (char*)rb->head + rb->sz;
	if(rb->head == rb->buffer_end)
		rb->head = rb->buffer;

	rb->count++;
	return retval;	
}

/*
 * Return 0 if success, -1 if buffer is empty
 * memory of item needs to be allocated by calling function
 */
int ringbuf_popfront(ring_buffer_t* rb, void* item)
{
	if(rb->count == 0)
		return -1;

	memcpy(item, rb->tail, rb->sz);
	rb->tail = (char*)rb->tail + rb->sz;
	if(rb->tail == rb->buffer_end)
		rb->tail = rb->buffer;

	rb->count--;
	return 0;
}



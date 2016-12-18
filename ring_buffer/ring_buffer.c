#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct _ring_buffer_t{
	void* buffer;
	void* buffer_end;
	size_t capacity; 		//max number of ITEMs in buffer
	size_t sz;					//sz of 1 item
	size_t count;				//number of items in the buffer
	void* head;
	void* tail;
}ring_buffer_t;

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

int main()
{
	int item;
	ring_buffer_t rb;
	ringbuf_init(&rb,5,sizeof(int));

	int i = 0;
	for(; i < 6; i++){
		if(ringbuf_pushback(&rb,&i))
			printf("Overwritten!\n");
	}

	for(i = 0; i < 10; i++){
		if(ringbuf_popfront(&rb,&item)){
			if(errno == ENOMEM)
				printf("Cannot allocate memory\n");
			printf("Nothing in ringbuf\n");
			break;
		}

		printf("Item popped: %d\n",item);
	}
	return 0;
}


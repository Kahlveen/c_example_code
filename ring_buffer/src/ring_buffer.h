#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _cpluscplus
extern {
#endif

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
int ringbuf_init(ring_buffer_t* rb, size_t capacity, size_t sz);

void ringbuf_free(ring_buffer_t* rb);

/*
 *	Returns 0 if nothing is overwritten,
 *	-1 if item is overwritten.
 */
int ringbuf_pushback(ring_buffer_t* rb, const void* item);

/*
 * Return 0 if success, -1 if buffer is empty
 * memory of item needs to be allocated by calling function
 */
int ringbuf_popfront(ring_buffer_t* rb, void* item);

#ifdef _cplusplus
}
#endif

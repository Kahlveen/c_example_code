#include "ring_buffer.h"

typedef struct _outer_t
{
	char* name;
	int age;

}outer_t;

void print_stuff(outer_t* o)
{
	printf("Name: %s\n",o->name);
	printf("Age: %d\n",o->age);
}

int main()
{
	ring_buffer_t rb;
	printf("Size of outer_t: %d\n",sizeof(outer_t));

	ringbuf_init(&rb,3,sizeof(outer_t));
	char somename[] = "Monkey king stephen chow";
	outer_t peeps[4];
	outer_t item;
	int i = 0;
	for(;i<4;++i){
		peeps[i].name = malloc(strlen(somename)+1);
		memcpy(peeps[i].name,somename,strlen(somename) + 1);
		peeps[i].age = i;
		if(ringbuf_pushback(&rb,(void*)&peeps[i]))
			printf("Overwritten!\n");
	}
	

	for(i = 0; i < 10; i++){
		if(ringbuf_popfront(&rb,&item)){
			printf("Nothing in ringbuf\n");
			break;
		}

		print_stuff(&item);

	}
	return 0;
}


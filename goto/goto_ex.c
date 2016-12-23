#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int test(int i)
{
	if(i%2)
		return -1;
	return 0;
}

int main()
{
	char toCpy[255] = {0};
	int i = 0;
	for(; i<4; i++){
		char* s = malloc (256);
		printf("%d: ",i);
		if(test(i))
			goto odd_no;
		else
			goto even_no;

odd_no:
		printf("odd_no\n");
		//without this continue, all the code below will still be executed
		continue;			

		printf("First printf.\n");

even_no:
		printf("even_no\n");
		continue;
		printf("Second printf.\n");
	}


	return 0;
}

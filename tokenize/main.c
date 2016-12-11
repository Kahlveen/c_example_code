#include <stdio.h>
#include <string.h>

int main()
{
	char* input = "one;two;three;four";
	char delim = ';';
	char* buf;

	char* prev = input;
	char* next = strchr(prev,delim);
	while(next != NULL)
	{
		buf = strndup(prev, (next - prev)); //no \0 at end. could be dangerous
		printf("%s\n",buf);
		prev = ++next;
		next = strchr(prev,delim);
		free(buf);
	}

	//To get last token if no ending ';'
	buf = strndup(prev, 10);
	printf("%s\n",buf);
	return 0;
}

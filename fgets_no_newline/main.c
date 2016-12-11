#include <stdio.h>
#include <string.h>
int main()
{
	FILE* fp = fopen("input.txt","r");
	char buf[255];

	while(fgets(buf,255,fp) != NULL)
	{
		buf[strcspn(buf,"\r\n")] = '\0';	//works for LF, CR, CRLF, LFCR
		if(strlen(buf) == 0)
		{
			printf("got here\n");
			continue;
		}

		else
			printf("%s\n",buf);
	}


	fclose(fp);

	return 0;
}

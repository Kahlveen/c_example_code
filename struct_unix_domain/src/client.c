#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "cli.h"

void usage(char* prog_name){
	printf("Usage:%s [info | stats]\n\n", prog_name);
}

int main(int argc, char **argv)
{
	enum command cmd = UNDEFINED;

	if(argc != 2){
		usage(argv[0]);
		exit(1);
	}

	if(strcmp(argv[1], "info") == 0)
		cmd = INFO;

	else if(strcmp(argv[1], "stats") == 0)
		cmd = STATS;

	else {
		usage(argv[0]);
		exit(1);
	}

	struct sockaddr_un addr;
	char buf[100];
	char *cli_socket = "/tmp/cli_test";
	int fd, cl;

	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("socket error");
		exit(-1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,cli_socket,sizeof(addr.sun_path)-1);

	if(connect(fd,(struct sockaddr*)&addr, sizeof(addr))){
		perror("connect error");
		exit(-1);
	}

	int num_read = 0;

	if(write(fd,&cmd, sizeof(cmd)) != sizeof(cmd)){
		printf("Cannot write command over");
		exit(-1);
	}

	struct info_t info;
	if( (num_read = read(fd,&info,sizeof(info))) > 0){
		printf("name: %s\n",info.name);	
		printf("Uptime: %d\n", info.uptime);
		printf("Someval: %d\n",info.some_val);
	}

	return 0;
}


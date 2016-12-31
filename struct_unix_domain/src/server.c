#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "cli.h"

int main(int argc, char** argv)
{
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
	unlink(cli_socket);

	if(bind(fd,(struct sockaddr*)&addr, sizeof(addr))){
		perror("bind error");
		exit(-1);
	}

	if(listen(fd,1)){
		perror("listen error");
		exit(-1);
	}

	while(1){
		if( (cl = accept(fd, NULL, NULL)) == -1){
			perror("accept error");
			continue;
		}

		int num_read = 0;
		int size_buf = 0;
		enum command cmd;

		struct info_t info;
		snprintf(info.name,sizeof(info.name),"%s",argv[0]);
		info.uptime = time(NULL);
		info.some_val = 999;

		if( ( num_read = read(cl, &cmd, sizeof(cmd))) > 0) {
			if(cmd == INFO){
				printf("INFO cmd\n");
				size_buf = 10;
				if(write(cl,&info, sizeof(info)) != sizeof(info)){
					printf("Write error");
				}
			}

			else if(cmd == STATS){
				printf("STATS cmd\n");
				size_buf = 999;
				if(write(cl,&size_buf, sizeof(size_buf)) != sizeof(size_buf)){
					printf("Write error");
				}
			}
		}

		else if(num_read == -1){
			perror("Read");
			exit(-1);
		}

		else if(num_read == 0){
			printf("EOF\n");
			close(cl);
		}
		sleep(1);
	}
	return 0;
}

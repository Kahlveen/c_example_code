#include <stdio.h>
#include <sys/inotify.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

void get_inotify_evt (struct inotify_event *i)
{
	printf("wd: %d \n",i->wd);
	if(i->cookie > 0)
		printf("cookie: %d\n",i->cookie);

	printf("mask: ");
	if (i->mask & IN_ACCESS)        printf("IN_ACCESS ");
	if (i->mask & IN_ATTRIB)        printf("IN_ATTRIB ");
	if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
	if (i->mask & IN_CLOSE_WRITE)   printf("IN_CLOSE_WRITE ");
	if (i->mask & IN_CREATE)        printf("IN_CREATE ");
	if (i->mask & IN_DELETE)        printf("IN_DELETE ");
	if (i->mask & IN_DELETE_SELF)   printf("IN_DELETE_SELF ");
	if (i->mask & IN_IGNORED)       printf("IN_IGNORED ");
	if (i->mask & IN_ISDIR)         printf("IN_ISDIR ");
	if (i->mask & IN_MODIFY)        printf("IN_MODIFY ");
	if (i->mask & IN_MOVE_SELF)     printf("IN_MOVE_SELF ");
	if (i->mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM ");
	if (i->mask & IN_MOVED_TO)      printf("IN_MOVED_TO ");
	if (i->mask & IN_OPEN)          printf("IN_OPEN ");
	if (i->mask & IN_Q_OVERFLOW)    printf("IN_Q_OVERFLOW ");
	if (i->mask & IN_UNMOUNT)       printf("IN_UNMOUNT ");
	printf("\n");

	if(i->len > 0)
		printf("len: %d\n",i->len);

	printf("Name: %s\n", i->name);

}

#define MAX_NAME_LEN 255
#define BUF_LEN (10 * (sizeof(struct inotify_event) + MAX_NAME_LEN + 1))	//+1 for \0

int main()
{
	int inotifyFd, wd, j;
	char buf[BUF_LEN];
	size_t num_read;
	char* p;
	struct inotify_event* evt = NULL;

	//IN_CLOSE_WRITE -> works for touch, cp, not for mv
	//IN_MOVED_FROM -> file moved from directory to somewhere else
	//IN_MOVED_TO -> file moved into directory
	int flags =  IN_ISDIR | IN_CLOSE_WRITE |IN_CREATE | IN_MOVED_TO	;

	//	inotifyFd = inotify_init();	//for blocking
	inotifyFd = inotify_init1(IN_NONBLOCK);	//for non-blocking
	if(inotifyFd == -1)
	{
		printf("Error on inotify_init");
		return -1;
	}

	wd = inotify_add_watch(inotifyFd, "f1", flags);
	printf("Watch %s on %d\n","f1",wd);
	
	wd = inotify_add_watch(inotifyFd, "f2", flags);
	printf("Watch %s on %d\n","f2",wd);

	while(true)
	{
		num_read = read(inotifyFd,buf,BUF_LEN);

		if(num_read == 0)
		{
			printf("FATAL: read gives 0\n");
			return -1;
		}

		if(num_read == -1)
		{
			printf("Read error");

			if(errno == EAGAIN)
			{
				printf(": EAGAIN\n");
				sleep(1);
				continue;
			}
			return -1;
		}

		printf("Read %ld bytes from inotifyFd\n",num_read);

		for(p = buf;p < buf+num_read;)
		{
			evt = (struct inotify_event*)p;
			get_inotify_evt(evt);
			p += sizeof(struct inotify_event) + evt->len;
		}

		sleep(1);
		printf("looping\n");
	}	

	
	return 0;
}

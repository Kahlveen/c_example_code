#ifndef __CLI__
#define __CLI__

enum command {INFO, STATS, UNDEFINED};

struct info_t{
	char name[255];
	time_t uptime;
	int some_val;
};
#endif

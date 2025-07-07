#include <sys/time.h>
#include <time.h>

#include "system.h"

uint64_t time_get() {
	struct timeval val;
	gettimeofday(&val, NULL);
	return ((uint64_t)val.tv_sec * (uint64_t)1000000) + (uint64_t)val.tv_usec;
}

uint64_t time_freq() {
	return 1000000;
}

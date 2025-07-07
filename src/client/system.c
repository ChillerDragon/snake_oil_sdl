#include <SDL3/SDL_timer.h>
#include <stdint.h>

#include "system.h"

uint64_t time_get() {
	return SDL_GetTicksNS();
}

uint64_t time_freq() {
	// the resulution of our timer is nanoseconds
	// so one billion nanoseconds is one second
	return 999999999;
}

#include "system.h"
#include <SDL3/SDL_timer.h>

Uint64 time_get() {
	return SDL_GetTicksNS();
}

Uint64 time_freq() {
	// the resulution of our timer is nanoseconds
	// so one billion nanoseconds is one second
	return 999999999;
}

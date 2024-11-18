#pragma once

#include <SDL3/SDL_stdinc.h>

// Time in nanoseconds using SDL_GetTicksNS()
Uint64 time_get();

// One second in time_get() units
//
// You can use it like this:
//
// ```c
// if((time_get() % time_freq()) == 0) {
// 	SDL_Log("one second passed ...");
// }
// ```
Uint64 time_freq();

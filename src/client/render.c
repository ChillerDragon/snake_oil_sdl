#include <SDL3/SDL_stdinc.h>

#include "system.h"

#include "render.h"

Uint64 get_max_frame_speed(int fps) {
	return time_freq() / fps;
}

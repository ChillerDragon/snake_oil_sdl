#pragma once

#include <SDL3/SDL_stdinc.h>

// returns the minimum amount of time
// it has to take to render one fps
// in nanoseconds (in other words the maximum speed)
//
// used to limit the ressources and not
// produce more than `fps` frames per second
Uint64 get_max_frame_speed(int fps);

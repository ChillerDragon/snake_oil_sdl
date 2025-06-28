#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "net_client.h"

#include "game.h"

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;

	// entire game state
	Game game;

	// networking
	NetClient client;

	// last update tick (SDL_GetTickNS)
	Uint64 last_tick;

	// last time the fps were refreshed (SDL_GetTickNS)
	// used to count the fps once a second
	Uint64 last_fps_refresh;

	// counts the frames but only holds
	// the real fps value once a second
	Uint64 fps_counter;

	// time in nanoseconds it took to render the
	// most recent frame
	Uint64 render_frame_time;

	// string holding the current fps
	// that will be shown to the user
	char fps_text[16];
} AppState;

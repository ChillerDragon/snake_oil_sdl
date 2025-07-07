// added by lsp do we even need this shits?
// SDL.h should have it all
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <stdint.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "app.h"
#include "app_state.h"
#include "game.h"
#include "key_event.h"
#include "render.h"
#include "system.h"

// this is the fixed update tick rate
// the render rate might be higher depending
// on how many fps your hardware can produce
// but the logic game_tick is called in a fixed rate
#define TICK_RATE_IN_NANOSECONDS 125000000

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

void parse_args(int argc, char *argv[]) {
	for(int i = 1; i < argc; i++) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "unused cli arg: %s", argv[i]);
	}
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
	parse_args(argc, argv);

	if(!SDL_Init(SDL_INIT_VIDEO)) {
		return SDL_APP_FAILURE;
	}

	AppState *as = SDL_calloc(1, sizeof(AppState));
	if(!as) {
		return SDL_APP_FAILURE;
	}
	*appstate = as;

	if(!SDL_CreateWindowAndRenderer("oiled snake", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &as->window, &as->renderer)) {
		return SDL_APP_FAILURE;
	}

	app_init(as);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	Game *game = &((AppState *)appstate)->game;
	if(event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	} else if(event->type == SDL_EVENT_KEY_DOWN) {
		return handle_key_event_down(game, event->key.scancode);
	} else if(event->type == SDL_EVENT_KEY_UP) {
		return handle_key_event_up(game, event->key.scancode);
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	AppState *as = (AppState *)appstate;
	Game *game = &as->game;
	const uint64_t now = time_get();

	// run game logic if we're at or past the time to run it.
	// if we're _really_ behind the time to run it, run it
	// several times.
	//
	// TODO: i think only the server has to do this?
	int ticks_behind = -1;
	while((now - as->last_tick) >= TICK_RATE_IN_NANOSECONDS) {
		app_tick(as);
		as->last_tick += TICK_RATE_IN_NANOSECONDS;
		ticks_behind++;
	}
	if(ticks_behind > 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%d ticks behind", ticks_behind);
	}

	if(now - as->last_fps_refresh > time_freq()) {
		as->last_fps_refresh = now;
		SDL_snprintf(as->fps_text, sizeof(as->fps_text), "%" SDL_PRIu64 " fps", as->fps_counter);
		as->fps_counter = 0;
	}
	as->fps_counter++;

	app_render(as);

	// limit fps to safe ressources (hard cap 1000)
	// this will also sleep a bit if you have less than 1000 fps
	// because it limits individual frame times
	// and if you have an average of 200 fps but one fps rendered super fast
	// it will still sleep a bit
	as->render_frame_time = time_get() - now;
	Uint64 min_frame_time = get_max_frame_speed(1000);
	if(as->render_frame_time < min_frame_time) {
		// i get varying frame times on my laptop
		// one frame might be 12717007 ns which would expand to 78 fps
		// and the next frame time might be only 296050 ns which would expand to 3377 fps
		// it does not really depend on the update being called or not
		// not sure if such a high jitter is normal
		// it cant be good ...
		//
		// anyways it is not noticable to the naked eye
		// it looks quite stable but the question is what happens if we introduce heavier
		// logic ticks and more expensive render calls
		// the logic tick is not even called every frame so that is a jitter by it self
		// but i think rendering is that much more expensive that it has no effect
		// if we tick the update or not
		// SDL_Log("woah your computer is fast! You hit the max frame rate 🎉 (frame time in ns %" SDL_PRIu64 ") ticks=%d", as->render_frame_time, ticks_behind);
		SDL_DelayNS(min_frame_time - as->render_frame_time);
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	if(result == SDL_APP_SUCCESS) {
		SDL_Log("quitting ...");
	} else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "got error quiting ...");
	}

	AppState *as = (AppState *)appstate;
	app_shutdown(as);
	SDL_DestroyRenderer(as->renderer);
	SDL_DestroyWindow(as->window);
	SDL_free(as);
}

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
		return handle_key_event(game, event->key.scancode);
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	AppState *as = (AppState *)appstate;
	Game *game = &as->game;
	const Uint64 now = SDL_GetTicksNS();

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

	// TODO: move this to debug_hud.c
	// update fps counter every second (every one billion nanoseconds)
	if(now - as->last_fps_refresh > 999999999) // TODO: replace magic number 999999999 with time_freq like in teeworlds
	{
		as->last_fps_refresh = now;
		SDL_snprintf(as->fps_text, sizeof(as->fps_text), "%" SDL_PRIu64 " fps", as->fps_counter);
		as->fps_counter = 0;
	}
	as->fps_counter++;

	app_render(as);

	// TODO: move this to another file and make it one descriptive
	//       function call such as limit_fps()
	as->render_frame_time = SDL_GetTicksNS() - now;
	// TODO: replace this magic 999999 with a descriptive function call
	//       that computes the maximum amount of fps
	//       something like max_fps(1000) which then does time_freq / max_fps kind of things
	//       right now 999999 means 1000 fps because 999999999 / 999999 = 1000 which is a bit of a mess
	if(as->render_frame_time < 999999) {
		// TODO: wtf this prints for me? 1k fps on my laptop rly??? xd
		// SDL_Log("woah your computer is fast! You hit the max frame rate 🎉");
		SDL_DelayNS(999999 - as->render_frame_time);
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

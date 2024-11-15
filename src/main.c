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

#include "game.h"
#include "key_event.h"

#define STEP_RATE_IN_MILLISECONDS 125
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Game game;
	Uint64 last_step;
} AppState;

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

	game_init(&as->game);
	as->last_step = SDL_GetTicks();
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
	const Uint64 now = SDL_GetTicks();

	// run game logic if we're at or past the time to run it.
	// if we're _really_ behind the time to run it, run it
	// several times.
	//
	// TODO: i think only the server has to do this?
	int ticks_behind = -1;
	while((now - as->last_step) >= STEP_RATE_IN_MILLISECONDS) {
		game_tick(game);
		as->last_step += STEP_RATE_IN_MILLISECONDS;
		ticks_behind++;
	}
	if(ticks_behind > 0) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%d ticks behind", ticks_behind);
	}

	game_render(game, as->renderer);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	if(result == SDL_APP_SUCCESS) {
		SDL_Log("quitting ...");
	} else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "got error quiting ...");
	}

	AppState *as = (AppState *)appstate;
	game_shutdown(&as->game);
	SDL_DestroyRenderer(as->renderer);
	SDL_DestroyWindow(as->window);
	SDL_free(as);
}

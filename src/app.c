#include <SDL3/SDL_timer.h>

#include "app_state.h"
#include "game.h"

#include "app.h"

// called after window creation
void app_init(AppState *as) {
	// renderer and window at set by create window
	// all other fields are zero initialized by calloc

	game_init(&as->game);
	as->last_tick = SDL_GetTicksNS();
}

void app_tick(AppState *as) {
	game_tick(&as->game);
}

void app_render(AppState *as) {
	game_render(&as->game, as->renderer);

	SDL_SetRenderDrawColor(as->renderer, 255, 255, 255, 255);
	SDL_RenderDebugText(as->renderer, 0, 0, as->fps_text);
	SDL_RenderPresent(as->renderer);
}

void app_shutdown(AppState *as) {
	game_shutdown(&as->game);
}

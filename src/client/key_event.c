#include <SDL3/SDL_log.h>

#include "key_event.h"
#include "player.h"

SDL_AppResult handle_key_event(Game *game, SDL_Scancode key_code) {
	switch(key_code) {
	/* Quit. */
	case SDL_SCANCODE_ESCAPE:
	case SDL_SCANCODE_Q:
		SDL_Log("quit key");
		return SDL_APP_SUCCESS;
	case SDL_SCANCODE_A:
		player_move_left(game->players[0]);
		break;
	case SDL_SCANCODE_D:
		player_move_right(game->players[0]);
		break;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_DOWN:
		break;
	default:
		break;
	}
	return SDL_APP_CONTINUE;
}

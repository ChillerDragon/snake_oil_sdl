#include <SDL3/SDL_log.h>

#include "key_event.h"
#include "protocol/messages.h"

SDL_AppResult handle_key_event_down(Game *game, SDL_Scancode key_code) {
	MsgInput old_input = game->input;

	switch(key_code) {
	/* Quit. */
	case SDL_SCANCODE_ESCAPE:
	case SDL_SCANCODE_Q:
		SDL_Log("quit key");
		return SDL_APP_SUCCESS;
	case SDL_SCANCODE_A:
		game->input.direction = -1;
		break;
	case SDL_SCANCODE_D:
		game->input.direction = 1;
		break;
	default:
		break;
	}

	if(old_input.direction != game->input.direction) {
		game->input_changed = 1;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult handle_key_event_up(Game *game, SDL_Scancode key_code) {
	MsgInput old_input = game->input;

	switch(key_code) {
	case SDL_SCANCODE_A:
		if(game->input.direction == -1) {
			game->input.direction = 0;
		}
		break;
	case SDL_SCANCODE_D:
		if(game->input.direction == 1) {
			game->input.direction = 0;
		}
		break;
	default:
		break;
	}

	if(old_input.direction != game->input.direction) {
		game->input_changed = 1;
	}

	return SDL_APP_CONTINUE;
}

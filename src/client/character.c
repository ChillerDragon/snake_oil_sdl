#include <SDL3/SDL_stdinc.h>

#include <game/character.h>
#include <stdio.h>

#include "character.h"

void character_draw(Character *character, Camera *camera, SDL_Renderer *renderer) {
	SDL_FRect r = {
		.w = (float)character->width,
		.h = (float)character->height,
		.x = (float)character->pos.x,
		.y = (float)character->pos.y};

	camera_frect_world_to_screen(camera, &r);
	SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &r);

	char buf[512];
	snprintf(buf, sizeof(buf), "cid=%d x=%d y=%d", character->client_id, character->pos.x, character->pos.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDebugText(renderer, r.x, r.y - 10, buf);
}

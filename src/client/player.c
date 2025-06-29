#include "player.h"

#include <SDL3/SDL_stdinc.h>

void player_draw(Player *player, Camera *camera, SDL_Renderer *renderer) {
	SDL_FRect r = {
		.w = (float)player->width,
		.h = (float)player->height,
		.x = (float)player->pos.x,
		.y = (float)player->pos.y};

	camera_frect_world_to_screen(camera, &r);
	SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &r);
}

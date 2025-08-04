#include <SDL3/SDL_render.h>

#include <client/camera.h>
#include <client/game.h>
#include <game/game_world.h>
#include <stdio.h>

#include "hud.h"

void hud_draw(Game *game, SDL_Renderer *renderer, const char *fps_text) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDebugText(renderer, 0, 0, fps_text);

	char buf[512];
	snprintf(buf, sizeof(buf), "camera x=%d y=%d", game->camera.pos.x, game->camera.pos.y);
	SDL_RenderDebugText(renderer, 0, 10, buf);
}

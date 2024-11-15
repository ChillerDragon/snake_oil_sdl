#pragma once

#include <SDL3/SDL_rect.h>

#include "pos.h"

typedef struct {
	Pos pos;
	int zoom;
} Camera;

void camera_set_pos(Camera *camera, Pos pos);
void camera_pos_world_to_screen(Camera *camera, Pos *pos);
void camera_frect_world_to_screen(Camera *camera, SDL_FRect *rect);

#include "camera.h"

void camera_set_pos(Camera *camera, Pos pos) {
	camera->pos = pos;
}

void camera_pos_world_to_screen(Camera *camera, Pos *pos) {
	pos->x -= camera->pos.x;
	pos->y -= camera->pos.y;
}

void camera_frect_world_to_screen(Camera *camera, SDL_FRect *rect) {
	rect->x -= (float)camera->pos.x;
	rect->y -= (float)camera->pos.y;
	rect->w *= (float)camera->zoom;
	rect->h *= (float)camera->zoom;
}

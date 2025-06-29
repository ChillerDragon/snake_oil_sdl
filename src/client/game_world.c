#include <client/character.h>
#include <game/game_world.h>
#include <shared/logger.h>

void gameworld_draw(GameWorld *world, Camera *camera, SDL_Renderer *renderer) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Character *character = world->characters[i];
		if(!character)
			continue;

		log_info("gameworld", "drawing character with id %d", i);
		character_draw(character, camera, renderer);
	}
}

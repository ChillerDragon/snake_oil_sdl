#include <SDL3/SDL_timer.h>

#include <client/hud.h>
#include <protocol/protocol.h>

#include "app_state.h"
#include "game.h"
#include "net_client.h"

#include "app.h"

// called after window creation
void app_init(AppState *as) {
	// renderer and window at set by create window
	// all other fields are zero initialized by calloc

	game_init(&as->game);
	netclient_init(&as->client);
	netclient_connect(&as->client, "127.0.0.1:8303");
	as->last_tick = SDL_GetTicksNS();
}

void app_tick(AppState *as) {
	game_tick(&as->game);

	unsigned char data[NET_MAX_PACKETSIZE];
	ssize_t bytes = netclient_recv(&as->client, data, sizeof(data));
	if(bytes > 0) {
		game_on_data(&as->game, data, bytes);
	}
}

void app_render(AppState *as) {
	game_render(&as->game, as->renderer);
	hud_draw(&as->game, as->renderer, as->fps_text);
	SDL_RenderPresent(as->renderer);
}

void app_shutdown(AppState *as) {
	game_shutdown(&as->game);
}

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <shared/logger.h>
#include <shared/system.h>

#include <server/system.h>

#include "server_state.h"

#include "server.h"

#define SERVER_TICK_RATE 2000000

int main() {
	log_info("server", "starting ...");

	ServerState server;
	server_init(&server);

	uint64_t last_tick = time_get();

	while(1) {
		const uint64_t now = time_get();
		int ticks_behind = -1;
		while((now - last_tick) >= SERVER_TICK_RATE) {
			log_info("server", "tick %ld", last_tick);
			server_tick(&server);
			last_tick += SERVER_TICK_RATE;
			ticks_behind++;
		}
		if(ticks_behind > 0) {
			log_error("server", "%d ticks behind", ticks_behind);
		}

		// TODO: move networking read out of the fixed tick rate?
	}
}

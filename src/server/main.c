#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <shared/logger.h>
#include <shared/system.h>

#include "server_state.h"

#include "server.h"

int main() {
	log_info("server", "starting ...");

	ServerState server;
	server_init(&server);

	while(1) {
		server_tick(&server);
	}
}

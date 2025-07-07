#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "system.h"

void str_hex(char *dst, int dst_size, const void *data, size_t data_size) {
	static const char hex[] = "0123456789ABCDEF";
	int data_index;
	int dst_index;
	for(data_index = 0, dst_index = 0; data_index < data_size && dst_index < dst_size - 3; data_index++) {
		dst[(ptrdiff_t)data_index * 3] = hex[((const unsigned char *)data)[data_index] >> 4];
		dst[(data_index * 3) + 1] = hex[((const unsigned char *)data)[data_index] & 0xf];
		dst[(data_index * 3) + 2] = ' ';
		dst_index += 3;
	}
	dst[dst_index] = '\0';
}

void addr_to_str(const struct sockaddr_in *addr, char *buf, size_t buf_size) {
	const unsigned char *ip = (const unsigned char *)&addr->sin_addr.s_addr;
	snprintf(
		buf,
		buf_size,
		"%d.%d.%d.%d:%u",
		ip[0],
		ip[1],
		ip[2],
		ip[3],
		ntohs(addr->sin_port));
}

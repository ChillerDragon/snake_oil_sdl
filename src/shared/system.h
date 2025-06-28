#pragma once

#include <netinet/in.h>
#include <stddef.h>

void str_hex(char *dst, int dst_size, const void *data, size_t data_size);
void addr_to_str(const struct sockaddr_in *addr, char *buf, size_t buf_size);

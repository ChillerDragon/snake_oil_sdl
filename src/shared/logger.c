#include <stdarg.h>
#include <stdio.h>

void log_info(const char *system, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char msg[2048];
	vsnprintf(msg, sizeof(msg), fmt, args);
	printf("[%s] %s\n", system, msg);
	va_end(args);
}

void log_error(const char *system, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char msg[2048];
	vsnprintf(msg, sizeof(msg), fmt, args);
	printf("[%s] %s\n", system, msg);
	va_end(args);
}

void log_warn(const char *system, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char msg[2048];
	vsnprintf(msg, sizeof(msg), fmt, args);
	printf("[%s] %s\n", system, msg);
	va_end(args);
}

void log_debug(const char *system, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char msg[2048];
	vsnprintf(msg, sizeof(msg), fmt, args);
	printf("[%s] %s\n", system, msg);
	va_end(args);
}

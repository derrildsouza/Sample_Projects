#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_PORT 8080
#define MIN_PORT 1
#define MAX_PORT 65535
#define BUFFER_SIZE 1024

/*
 * Parses command line arguments.
 * Returns 0 on success, -1 on failure.
 */
int parse_arguments(int argc, char *argv[], char **ip_address, int *port);

#ifdef __cplusplus
}
#endif

#endif // COMMON_H

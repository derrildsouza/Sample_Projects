/*
 * Copyright (c) 2026 Derril
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"

int parse_arguments(int argc, char *argv[], char **ip_address, int *port) {
    int opt_char;
    char *endptr;
    long val;

    // Reset getopt
    optind = 1;

    while ((opt_char = getopt(argc, argv, "i:p:")) != -1) {
        switch (opt_char) {
            case 'i':
                /* Implements: SWE_CLI_002 */
                *ip_address = optarg;
                break;
            case 'p':
                /* Implements: SWE_SRV_002, SWE_CLI_003 */
                val = strtol(optarg, &endptr, 10);
                /* Implements: SWE_SRV_004, SWE_CLI_003 */
                if (endptr == optarg || *endptr != '\0' || val < MIN_PORT || val > MAX_PORT) {
                    fprintf(stderr, "Invalid port number: %s\n", optarg);
                    return -1;
                }
                *port = (int)val;
                break;
            default:
                fprintf(stderr, "Usage: %s [-i IP_ADDRESS] [-p PORT]\n", argv[0]);
                return -1;
        }
    }
    return 0;
}

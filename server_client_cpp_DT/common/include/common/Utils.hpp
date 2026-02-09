#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <string>

namespace common {

struct Arguments {
    std::string ip_address;
    int port;
};

/*
 * Parses command line arguments.
 * Throws std::runtime_error on failure.
 */
Arguments parse_arguments(int argc, char* argv[]);

} // namespace common

#endif // COMMON_UTILS_HPP

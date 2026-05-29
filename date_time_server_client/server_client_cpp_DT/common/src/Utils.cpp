#include "common/Utils.hpp"
#include "common/Constants.hpp"
#include <unistd.h>
#include <stdexcept>
#include <iostream>

namespace common {

Arguments parse_arguments(int argc, char* argv[]) {
    Arguments args;
    args.ip_address = "127.0.0.1"; // Default
    args.port = DEFAULT_PORT;

    int opt;
    // Reset getopt
    optind = 1;

    while ((opt = getopt(argc, argv, "i:p:")) != -1) {
        switch (opt) {
            case 'i':
                /* Implements: SWE_CLI_002 */
                args.ip_address = optarg;
                break;
            case 'p': {
                /* Implements: SWE_SRV_002, SWE_CLI_003 */
                std::string port_str = optarg;
                size_t pos;
                int val = std::stoi(port_str, &pos);
                if (pos != port_str.length()) { // Check if entire string was number
                    throw std::invalid_argument("Non-numeric port");
                }
                
                /* Implements: SWE_SRV_004, SWE_CLI_004 */
                if (val < MIN_PORT || val > MAX_PORT) {
                    throw std::out_of_range("Port out of range");
                }
                args.port = val;
                break;
            }
            default:
                throw std::runtime_error("Usage: " + std::string(argv[0]) + " [-i IP] [-p PORT]");
        }
    }
    return args;
}

} // namespace common

#include "common/Utils.hpp"
#include "common/Constants.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>

class TimeServer {
public:
    TimeServer(int port) : port_(port), server_fd_(-1) {
        /* Implements: SWE_SRV_004 */
        if (port < common::MIN_PORT || port > common::MAX_PORT) {
            throw std::out_of_range("Port out of range");
        }
    }

    ~TimeServer() {
        if (server_fd_ != -1) {
            close(server_fd_);
        }
    }

    void start() {
        /* Implements: SWE_SRV_001 */
        server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd_ == 0) {
            throw std::runtime_error("Socket creation failed");
        }

        int opt = 1;
        if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            throw std::runtime_error("Setsockopt failed");
        }

        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port_);

        if (bind(server_fd_, (struct sockaddr *)&address, sizeof(address)) < 0) {
            throw std::runtime_error("Bind failed");
        }

        if (listen(server_fd_, 3) < 0) {
            throw std::runtime_error("Listen failed");
        }

        std::cout << "Server listening on ANY:" << port_ << std::endl;

        while (true) {
            int new_socket;
            int addrlen = sizeof(address);
            /* Implements: SWE_SRV_001 */
            if ((new_socket = accept(server_fd_, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                std::cerr << "Accept failed" << std::endl;
                continue; 
            }

            handleClient(new_socket);
        }
    }

private:
    void handleClient(int socket_fd) {
        /* Implements: SWE_SRV_005 */
        time_t rawtime;
        time(&rawtime);
        std::string time_str = ctime(&rawtime);

        /* Implements: SWE_SRV_006 */
        send(socket_fd, time_str.c_str(), time_str.length(), 0);
        std::cout << "Time sent to client." << std::endl;
        close(socket_fd);
    }

    int port_;
    int server_fd_;
};

int main(int argc, char* argv[]) {
    try {
        common::Arguments args = common::parse_arguments(argc, argv);
        TimeServer server(args.port);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

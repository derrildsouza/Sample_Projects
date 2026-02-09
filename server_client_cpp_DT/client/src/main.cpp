#include "common/Utils.hpp"
#include "common/Constants.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <vector>

class TimeClient {
public:
    TimeClient(const std::string& server_ip, int port) : server_ip_(server_ip), port_(port), sock_(-1) {
        /* Implements: SWE_CLI_004 */
        if (port < common::MIN_PORT || port > common::MAX_PORT) {
            throw std::out_of_range("Port out of range");
        }
    }

    ~TimeClient() {
        if (sock_ != -1) {
            close(sock_);
        }
    }

    void requestTime() {
        /* Implements: SWE_CLI_001 */
        sock_ = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_ < 0) {
            throw std::runtime_error("Socket creation error");
        }

        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port_);

        if (inet_pton(AF_INET, server_ip_.c_str(), &serv_addr.sin_addr) <= 0) {
            throw std::runtime_error("Invalid address/ Address not supported");
        }

        if (connect(sock_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            throw std::runtime_error("Connection Failed");
        }

        /* Implements: SWE_CLI_004 */
        std::vector<char> buffer(common::BUFFER_SIZE);
        int valread = read(sock_, buffer.data(), common::BUFFER_SIZE);
        if (valread > 0) {
            std::cout << "Server time: " << std::string(buffer.data(), valread);
        } else {
            std::cerr << "Failed to read data" << std::endl;
        }
    }

private:
    std::string server_ip_;
    int port_;
    int sock_;
};

int main(int argc, char* argv[]) {
    try {
        common::Arguments args = common::parse_arguments(argc, argv);
        TimeClient client(args.ip_address, args.port);
        client.requestTime();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

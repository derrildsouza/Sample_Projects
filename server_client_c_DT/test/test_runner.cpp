#include <gtest/gtest.h>
#include "common.h"

// Helper to reset getopt state before each test
void reset_getopt() {
    optind = 1;
}

/* Verifies: SWE_CLI_002, SWE_SRV_002 */
TEST(ParseArgumentsTest, ValidInput_IP_Port) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-i", (char*)"192.168.1.1", (char*)"-p", (char*)"1234"};
    int argc = 5;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), 0);
    EXPECT_STREQ(ip, "192.168.1.1");
    EXPECT_EQ(port, 1234);
}

/* Verifies: SWE_SRV_002, SWE_CLI_003 */
TEST(ParseArgumentsTest, ValidInput_PortOnly) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"9090"};
    int argc = 3;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), 0);
    EXPECT_EQ(ip, nullptr);
    EXPECT_EQ(port, 9090);
}

/* Verifies: SWE_SRV_003 */
TEST(ParseArgumentsTest, ValidInput_IPOnly) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-i", (char*)"10.0.0.1"};
    int argc = 3;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), 0);
    EXPECT_STREQ(ip, "10.0.0.1");
    EXPECT_EQ(port, DEFAULT_PORT);
}

/* Verifies: SWE_SRV_004, SWE_CLI_003 */
TEST(ParseArgumentsTest, InvalidInput_PortRangeHigh) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"70000"};
    int argc = 3;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    // Suppress stderr for expected errors
    testing::internal::CaptureStderr();
    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), -1);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("Invalid port number"), std::string::npos);
}

/* Verifies: SWE_SRV_004, SWE_CLI_004 */
TEST(ParseArgumentsTest, InvalidInput_PortRangeLow) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"0"};
    int argc = 3;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    testing::internal::CaptureStderr();
    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), -1);
    testing::internal::GetCapturedStderr();
}

/* Verifies: SWE_CLI_004 */
TEST(ParseArgumentsTest, InvalidInput_PortNonNumeric) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"abc"};
    int argc = 3;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    testing::internal::CaptureStderr();
    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), -1);
    testing::internal::GetCapturedStderr();
}

TEST(ParseArgumentsTest, UnknownOption) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-x"};
    int argc = 2;
    char* ip = NULL;
    int port = DEFAULT_PORT;

    testing::internal::CaptureStderr();
    EXPECT_EQ(parse_arguments(argc, argv, &ip, &port), -1);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("Usage:"), std::string::npos); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

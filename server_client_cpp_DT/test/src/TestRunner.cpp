#include <gtest/gtest.h>
#include "common/Utils.hpp"
#include "common/Constants.hpp"

// Helper to reset getopt state is tricky in C++ if we use the same global, 
// but we used ::optind in Utils.cpp. We need to reset it before calls if we link against it.
// However, since we are testing common::parse_arguments, let's see if we can manipulate optind.

extern int optind;

void reset_getopt() {
    optind = 1;
}

/* Verifies: SWE_CLI_002, SWE_SRV_002 */
TEST(ParseArgumentsTest, ValidInput_IP_Port) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-i", (char*)"192.168.1.1", (char*)"-p", (char*)"1234"};
    int argc = 5;
    
    common::Arguments args = common::parse_arguments(argc, argv);
    EXPECT_EQ(args.ip_address, "192.168.1.1");
    EXPECT_EQ(args.port, 1234);
}

/* Verifies: SWE_SRV_002, SWE_CLI_003 */
TEST(ParseArgumentsTest, ValidInput_PortOnly) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"9090"};
    int argc = 3;

    common::Arguments args = common::parse_arguments(argc, argv);
    EXPECT_EQ(args.ip_address, "127.0.0.1");
    EXPECT_EQ(args.port, 9090);
}

/* Verifies: SWE_SRV_003 */
TEST(ParseArgumentsTest, ValidInput_IPOnly) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-i", (char*)"10.0.0.1"};
    int argc = 3;

    common::Arguments args = common::parse_arguments(argc, argv);
    EXPECT_EQ(args.ip_address, "10.0.0.1");
    EXPECT_EQ(args.port, common::DEFAULT_PORT);
}

/* Verifies: SWE_SRV_004, SWE_CLI_004 */
TEST(ParseArgumentsTest, InvalidInput_PortRangeHigh) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"70000"};
    int argc = 3;

    EXPECT_THROW({
        common::parse_arguments(argc, argv);
    }, std::out_of_range);
}

/* Verifies: SWE_SRV_004, SWE_CLI_004 */
TEST(ParseArgumentsTest, InvalidInput_PortRangeLow) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"0"};
    int argc = 3;

    EXPECT_THROW({
        common::parse_arguments(argc, argv);
    }, std::out_of_range);
}

/* Verifies: SWE_CLI_004 */
TEST(ParseArgumentsTest, InvalidInput_PortNonNumeric) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-p", (char*)"abc"};
    int argc = 3;

    EXPECT_THROW({
        common::parse_arguments(argc, argv);
    }, std::invalid_argument);
}

TEST(ParseArgumentsTest, UnknownOption) {
    reset_getopt();
    char* argv[] = {(char*)"prog", (char*)"-x"};
    int argc = 2;

    EXPECT_THROW({
        common::parse_arguments(argc, argv);
    }, std::runtime_error); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

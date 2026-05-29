find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_runner_cpp src/TestRunner.cpp)
target_link_libraries(test_runner_cpp PRIVATE common_cpp ${GTEST_LIBRARIES} pthread)

add_test(NAME ArgumentParsingTestCPP COMMAND test_runner_cpp)

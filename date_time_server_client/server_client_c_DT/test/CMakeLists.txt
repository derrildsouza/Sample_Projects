find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_runner test_runner.cpp)
target_link_libraries(test_runner PRIVATE common ${GTEST_LIBRARIES} pthread)

add_test(NAME ArgumentParsingTest COMMAND test_runner)

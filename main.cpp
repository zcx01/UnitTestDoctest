#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <thread>
#include "test/maintest.hpp"

TEST_CASE("main test runing") {
//test_main();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
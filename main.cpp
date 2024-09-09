#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <thread>
#include "fds_can_main_entry.hpp"
#include "test/maintest.hpp"

TEST_CASE("main test runing") {
    init_signal_process();
    test_main();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

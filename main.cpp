#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Internal_message_center.h"
#include "test.hpp"

#define ICCHECK(topic,value,func,...) {func(topic,__VA_ARGS__);\
std::string topicValue;\
fds::getTopicValue(topic,topicValue);\
CHECK(topicValue == value);\
}

TEST_CASE("testing the factorial function") {
    // CHECK(fact(0) == 1); // should fail
    // test().test_function("test_topic","hello");
    
    ICCHECK("test_topic","hello",test().test_function,"hello")
    
}

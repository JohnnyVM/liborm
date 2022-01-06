#include <string>

#include "type/datetime.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Datetime){};

/* Notice: This tests define a couple of debatable behaviours */
TEST(Datetime, get_time_now) {
    Datetime dt{"now"};
    CHECK(not std::string(dt).empty());
}

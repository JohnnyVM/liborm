#include "CppUTest/TestHarness.h"

#include <decimal/decimal>

#include "type/numeric.hpp"

TEST_GROUP(numeric){};

TEST(numeric, cast_and_equal)
{
    orm::type::Numeric numeric{10, 10, 12.546};
    // cast to int
    CHECK(12 != numeric);
    CHECK(numeric != 12);
    CHECK(numeric == numeric);
    //CHECK(numeric == 12.546); // not allowed
}
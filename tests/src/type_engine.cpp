#include <string>
#include <decimal/decimal>
#include <iostream>
#include <iomanip>

#include "liborm/type/numeric.hpp"
#include "liborm/type/string.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(typeengine){};

TEST(typeengine, numeric_to_string)
{
    std::stringstream stream;
    long double fnum = 12.546L;
    orm::type::Numeric numeric{2U, 3U, fnum};
    const TypeEngine &alias = numeric;

    using std::to_string;
    stream << std::fixed << std::setprecision(numeric.scale) << fnum;
    CHECK_EQUAL(to_string(alias), stream.str());
    CHECK_EQUAL(std::string(alias), stream.str());
}

TEST(typeengine, string_to_string)
{
    std::string base = "hi!";
    orm::type::String str{base};
    const TypeEngine &alias = str;

    CHECK_EQUAL(to_string(alias), base);
}
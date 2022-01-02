#include <string>
#include <decimal/decimal>
#include <iostream>
#include <iomanip>

#include "type/numeric.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(typeengine){};

TEST(typeengine, numeric_to_string)
{
    std::stringstream stream;
    long double fnum = 12.546L;
    orm::type::Numeric numeric{2, 3, fnum};
    const orm::TypeEngine &alias = numeric;

    using std::to_string;
    stream << std::fixed << std::setprecision(numeric.scale) << fnum;
    CHECK_EQUAL(to_string(alias), stream.str());
}
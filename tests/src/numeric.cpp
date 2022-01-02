#include <decimal/decimal>
#include "type/engine.hpp"
#include "type/numeric.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(numeric){};

TEST(numeric, cast_integer)
{
    long double fnum = 12.146L;
    orm::type::Numeric numeric{2, 0, fnum}; // at this point technically basically lost the digits
    // cast to int
    using std::to_string;
    CHECK_TEXT(int(fnum) == numeric, std::string("value: "+ to_string(numeric) + " expected " + to_string(int(fnum))).c_str()); // no throw, integer and integer

    long double fnum2 = 12.546L;
    orm::type::Numeric numeric2{2, 1, fnum};
    // cast to int
    try {
        CHECK(int(fnum2) == numeric2); // throw, decimal vs integer
    } catch(const std::length_error&) {
        CHECK(1);
    } catch(...) {
        FAIL("Invalid exception throw");
    }
    try {
        CHECK(int(fnum2) == (int)numeric2); // forced cast
    } catch(...) {
        FAIL("Invalid exception throw");
    }
}

TEST(numeric, cast_numeric)
{
    long double fnum = 12.546L;
    orm::type::Numeric numeric{2, 3, fnum};
    // cast to int
    CHECK(int(fnum) == numeric);
    CHECK(numeric == int(fnum));
    CHECK(numeric == fnum);
    CHECK((long double)numeric == fnum);
    // TODO rest of the operators
}

TEST(numeric, int_op_equivalence)
{
    int inum = 12.546L;
    orm::type::Numeric numeric{2, 0, inum};
    // cast to int
    CHECK(numeric + 1 == inum + 1);
    CHECK(numeric * 2 == inum * 2);
    CHECK(numeric / 2 == inum / 2);
    CHECK(numeric - 1 == inum - 1);
}

/**
 * \brief Construct a new TEST object
 */
TEST(numeric, float_op_equivalence)
{
    float inum = 12.546L;
    orm::type::Numeric numeric{2, 3, inum};
    // cast to int
    CHECK(numeric + 1 == inum + 1);
    CHECK(numeric * 2 == inum * 2);
    CHECK(numeric / 2 == inum / 2);
    CHECK(numeric - 1 == inum - 1);
}
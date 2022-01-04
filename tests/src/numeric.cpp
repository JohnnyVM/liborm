#include <decimal/decimal>
#include "type/engine.hpp"
#include "type/numeric.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(numeric){};

TEST(numeric, cast_integer)
{
    long double fnum = 12.146L;
    orm::type::Numeric numeric{2, 3, fnum}; // ??? waht happen with the digits, teorically this case is not realistic
    // cast to int
    using std::to_string;
    CHECK(int(fnum) != numeric);

    long double fnum2 = 12.546L;
    orm::type::Numeric numeric2{2, 3, fnum};
    // cast to int
    try {
        CHECK(int(fnum2) != numeric2); // throw, decimal vs integer
    } catch(const std::length_error&) {
        CHECK(1);
    }
    CHECK(int(fnum2) == (int)numeric2); // forced cast
    CHECK(int(fnum2) == int(numeric2)); // forced cast
}

TEST(numeric, cast_numeric)
{
    long double fnum = 12.546L;
    orm::type::Numeric numeric{2, 3, fnum};
    // cast to int
    CHECK(int(fnum) != numeric);
    CHECK(int(fnum) == int(numeric));
    CHECK(numeric != int(fnum));
    //CHECK(int(numeric) == int(fnum));
    //CHECK(numeric == fnum);
    CHECK((long double)numeric == fnum);
    // TODO rest of the operators
}

TEST(numeric, int_op_equivalence)
{
    int inum = 12.546L;
    //float fnum = 12.546L;
    orm::type::Numeric numeric{2, 0, inum};
    // cast to int
    CHECK(numeric + 1 == inum + 1);
    CHECK(numeric * 2 == inum * 2);
    CHECK(numeric / 2 == inum / 2);
    CHECK(numeric - 1 == inum - 1);
    /*CHECK(numeric + 1 != fnum + 1);
    CHECK(numeric * 2 != fnum * 2);
    CHECK(numeric / 2 != fnum / 2);
    CHECK(numeric - 1 != fnum - 1);*/

    orm::type::Numeric numeric2{2, 1, 12.546L};
    // cast to int
    CHECK(numeric2 + 1 != inum + 1);
    CHECK(numeric2 * 2 != inum * 2);
    CHECK(numeric2 / 2 != inum / 2);
    CHECK(numeric2 - 1 != inum - 1);
    /*CHECK(numeric + 1 == fnum + 1);
    CHECK(numeric * 2 == fnum * 2);
    CHECK(numeric / 2 == fnum / 2);
    CHECK(numeric - 1 == fnum - 1);*/

    /** ??? i dont know what do here */
    /*orm::type::Numeric numeric3{2, 0, 12.546L};
    // cast to int
    CHECK(numeric3 + 1 == inum + 1);
    CHECK(numeric3 * 2 == inum * 2);
    CHECK(numeric3 / 2 == inum / 2);
    CHECK(numeric3 - 1 == inum - 1);*/
}

/**
 * \brief Construct a new TEST object
 * \todo i dont know what do here
 */
/*TEST(numeric, float_op_equivalence)
{
    float inum = 12.546L;
    orm::type::Numeric numeric{2, 3, inum};
    // cast to int
    CHECK(numeric + 1 == inum + 1);
    CHECK(numeric * 2 == inum * 2);
    CHECK(numeric / 2 == inum / 2);
    CHECK(numeric - 1 == inum - 1);
}*/
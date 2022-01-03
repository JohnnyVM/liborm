#include <string>

#include "type/string.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(String){};

TEST(String, cast_string) {
	orm::type::String str(3, "Hi!");

	CHECK_EQUAL(std::string("Hi!"), std::string(str));

	try {
		orm::type::String(3, "Hi!!");
	} catch(const std::length_error& err) {
		CHECK(1);
	} catch(...) {
		FAIL("Invalid exception");
	}

	orm::type::String test(9, "Hi ");
	CHECK_EQUAL(std::string("Hi world!"), test + std::string("world!"));
	CHECK_EQUAL(std::string("Hi world!"), test + "world!");
	CHECK_EQUAL(std::string("Hi world!"), std::string("Hi ") + orm::type::String(7, "world!"));
	CHECK_EQUAL(std::string("Hi world!"), "Hi " + orm::type::String(7, "world!"));
	test += "world!";
	CHECK(test == "Hi world!");
	CHECK(test == std::string("Hi world!"));
	CHECK(test != "Hi world! 1");
	CHECK(test != std::string("Hi world! 2"));
	//CHECK_EQUAL(std::string("Hi world!"), test);
	//CHECK_EQUAL("Hi world!", test);
}

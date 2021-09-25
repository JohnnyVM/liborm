#include "CppUTest/TestHarness.h"

#include <typeinfo>

#include "column.hpp"

TEST_GROUP(Column){};

TEST(Column, initialicer){
	// only for test the compilation
	orm::Column col({
			{.name = "col"}, // base class
			.default_value = nullptr,
			.primary_key = false,
			.nullable = false
	});
	CHECK(1);
};


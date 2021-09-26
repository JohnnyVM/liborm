#include "CppUTest/TestHarness.h"

#include <typeinfo>

#include "column.hpp"
#include "column/string.hpp"
#include "column/integer.hpp"

TEST_GROUP(Column){};

TEST(Column, initialicer){
	// only for test the compilation
	orm::Column col({
			{.name = "col"}, // base class
			.type = new orm::String(12),
			.primary_key = false,
			.nullable = false,
			.default_value = nullptr
	});
	orm::Column col_2{{
			.name = "col", // base class
			.type = new orm::Integer(),
			.primary_key = false,
			.nullable = false,
			.default_value = nullptr
	}};
	// other initializacion way
	/*orm::Column col_2({
			{"col"}, // base class
			.primary_key = false,
			.nullable = false,
			.default_value = nullptr
	});*/
	CHECK(1);
};

#include "CppUTest/TestHarness.h"

#include <string>
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
	CHECK(1);
};

TEST(Column, to_string){
	orm::Column col{{
			.name = "col", // base class
			.type = new orm::Integer(),
			.primary_key = false,
			.nullable = false,
			.default_value = nullptr
	}};
	CHECK_EQUAL((std::string)col, (std::string)"col integer not null");

	orm::Column col_2{{
			.name = "col", // base class
			.type = new orm::String(0),
			.primary_key = true,
			.nullable = false,
			.default_value = nullptr
	}};
	CHECK_EQUAL((std::string)col_2, (std::string)"col character varying(1) primary key not null");
};

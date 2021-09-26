#include "CppUTest/TestHarness.h"

#include <typeinfo>

#include "column.hpp"
#include "table.hpp"

TEST_GROUP(Table){};

TEST(Table, initialicer){
	// only for test the compilation
	orm::Table table_2(
			"table", // name
			{ // Columns
				new orm::Column({.name = "colum_1", .primary_key=true, .nullable=true, .default_value=nullptr})
			}
	);
	CHECK(1);
};


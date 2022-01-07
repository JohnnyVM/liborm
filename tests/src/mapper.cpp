#include "mapper/column.hpp"
#include "mapper/string.hpp"
#include "mapper/integer.hpp"
#include "mapper/table.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Column){};

TEST(Column, initialicer){
	// only for test the compilation
	orm::Column col{{
			.name = "col", // base class
			.type = orm::String(12),
			.primary_key = false,
			.nullable = false,
			.default_value = nullptr
	}};
	orm::Column col_2{{
			.name = "col", // base class
			.type = orm::Integer(),
			.primary_key = false,
			.nullable = false,
			.default_value = nullptr
	}};
	CHECK(1);
};


/*TEST_GROUP(Table){};

TEST(Table, mapper_table){
	// only for test the compilation, not require dfine all
	orm::Table table(
			"table", // name
			{ // Columns
				orm::column({
						.name = "colum_1",
						.type = orm::String(16),
						.primary_key=false,
						.nullable=true,
						.default_value=nullptr}),
				orm::column({
						.name = "colum_2",
						.type = orm::Integer(),
						.primary_key=true,
						.nullable=false,
						.default_value=nullptr})
			}
	);
	CHECK(table.name == "table");
};*/

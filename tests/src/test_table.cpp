#include <typeinfo>

#include "column.hpp"
#include "column/string.hpp"
#include "column/integer.hpp"
#include "table.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Table){};

TEST(Table, initialicer){
	// only for test the compilation, not require dfine all
	orm::Table table_2(
			"table", // name
			{ // Columns
				orm::column({
						.name = "colum_1",
						.type = new orm::String(16),
						.primary_key=false,
						.nullable=true,
						.default_value=nullptr
				}),

				orm::column({
						.name = "colum_2",
						.type = new orm::Integer(),
						.primary_key=true,
						.nullable=false,
						.default_value=nullptr
				})

			}
	);
	CHECK(1);
};


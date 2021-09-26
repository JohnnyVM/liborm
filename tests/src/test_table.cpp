#include "CppUTest/TestHarness.h"

#include <typeinfo>

#include "column.hpp"
#include "column/string.hpp"
#include "column/integer.hpp"
#include "table.hpp"

TEST_GROUP(Table){};

TEST(Table, initialicer){
	// only for test the compilation, not require dfine all
	orm::Table table_2(
			"table", // name
			{ // Columns
				new orm::Column({
						.name = "colum_1",
						.type = new orm::String(16),
						.primary_key=true,
						.nullable=true,
						.default_value=nullptr
				}),

				new orm::Column({
						.name = "colum_2",
						.type = new orm::Integer(),
						.primary_key=true,
						.nullable=true,
						.default_value=nullptr
				})

			}
	);
	CHECK(1);
};


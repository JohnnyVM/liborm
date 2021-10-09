#include "CppUTest/TestHarness.h"

#include "column.hpp"
#include "column/string.hpp"
#include "column/integer.hpp"
#include "table.hpp"
#include "select.hpp"

TEST_GROUP(select){};

TEST(select, initialicer) {

	// only for test the compilation, not require dfine all
	orm::Table table(
			"table", // name
			{ // Columns
				orm::column({
						.name = "colum_1",
						.type = new orm::String(16),
						.primary_key=true,
						.nullable=true,
						.default_value=nullptr
				}),

				orm::column({
						.name = "colum_2",
						.type = new orm::Integer(),
						.primary_key=true,
						.nullable=true,
						.default_value=nullptr
				})

			}
	);

	orm::Select select(&table);
	CHECK_EQUAL((std::string)select, (const std::string)"select table.colum_1,table.colum_2 from table");

	//CHECK_EQUAL((std::string)select(&table), (const std::string)"select table.colum_1,table.colum_2 from table");
};


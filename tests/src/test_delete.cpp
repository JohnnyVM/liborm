#include "CppUTest/TestHarness.h"

#include "column.hpp"
#include "column/string.hpp"
#include "column/integer.hpp"
#include "table.hpp"
#include "delete.hpp"

TEST_GROUP(deleter){};

TEST(deleter, initialicer) {

	// only for test the compilation, not require dfine all
	orm::Table table(
			"table", // name
			{ // Columns
				new orm::Column({
						.name = "colum_1",
						.type = new orm::String(16),
						.primary_key=true,
						.nullable=true,
						.default_value=nullptr
				}),
			}
	);

	orm::Delete del(&table);
	CHECK_EQUAL(std::string(del), (const std::string)"delete from table");
};



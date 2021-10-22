#include "CppUTest/TestHarness.h"

#include "column.hpp"
#include "column/string.hpp"
#include "column/integer.hpp"
#include "table.hpp"
#include "insert.hpp"

TEST_GROUP(Insert){};

TEST(Insert, initialicer) {

	// only for test the compilation, not require dfine all
	orm::Table table(
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

	// Simple constructor
	orm::Insert insert;
	// No values passed
	CHECK_EQUAL((std::string)insert(&table), (const std::string)"insert into table colum_1,colum_2 values(:colum_1,:colum_2)");
	// equivalent
	CHECK_EQUAL((std::string)table.insert(), (const std::string)"insert into table colum_1,colum_2 values(:colum_1,:colum_2)");


	insert(&table).values("colum_2", "5");
	CHECK_EQUAL((std::string)insert, (const std::string)"insert into table colum_2 values(:colum_2)");

	insert.values("colum_1", 5);
	CHECK_EQUAL((const std::string)"insert into table colum_1,colum_2 values(:colum_1,:colum_2)", (std::string)insert);

	//chain constructor
	orm::Insert sinsert;
	sinsert(&table)
		.values("colum_2", "5")
		.values("colum_1", 5);
	CHECK_EQUAL((const std::string)"insert into table colum_1,colum_2 values(:colum_1,:colum_2)", (std::string)sinsert);
};


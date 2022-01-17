#include "mapper/column.hpp"
#include "liborm/type/string.hpp"
#include "liborm/type/numeric.hpp"
#include "mapper/table.hpp"

#include "CppUTest/TestHarness.h"
#include "liborm/type/types.hpp"

TEST_GROUP(Column){};

TEST(Column, mapper_column){
	// only for test the compilation
	orm::Column col_1("col", orm::Numeric(19,9));
	orm::Column col_2("col", orm::Numeric(19));
	orm::Column col_3("col", orm::String(0));
	orm::Column col_4("col", orm::String(16));
	orm::Column col_5("col", orm::String(16), {.primary_key = true, .nullable = false});
	orm::Column col_6("col", orm::String(16), {.primary_key = false, .nullable = false});
	CHECK(1);
};


TEST_GROUP(Table){};

TEST(Table, mapper_table){
	// only for test the compilation, not require dfine all
	orm::Table table(
			"table",
			{
				orm::column("col", orm::Numeric(19,9)),
				orm::column("col", orm::Numeric(19), {.primary_key = true, .nullable = false})
			}
	);
	CHECK(table.name == "table");
};

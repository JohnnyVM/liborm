#ifndef LIBORM_COLUMN_INTEGER_HPP
#define LIBORM_COLUMN_INTEGER_HPP

#include <string>
#include <cstdint>

#include "column/base.hpp"

namespace orm {

class Integer : public orm::ColumnType { // Keep that separate for class slicing
	public:
	Integer() : orm::ColumnType(sizeof(intmax_t)) {}
	const std::string display_name = "integer";
	explicit operator const std::string() override { return display_name; };
};

}

#endif


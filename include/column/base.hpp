#ifndef LIBORM_COLUMN_BASE_HPP
#define LIBORM_COLUMN_BASE_HPP

#include <cstdlib>
#include <string>

namespace orm {

class ColumnType { // Keep that separate for class slicing
	public:
	const size_t length;
	virtual ~ColumnType(){}
	ColumnType(size_t arg_length) : length(arg_length) {}

	virtual explicit operator const std::string() = 0;
};

}

#endif

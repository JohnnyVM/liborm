#ifndef LIBORM_COLUMN_BASE_HPP
#define LIBORM_COLUMN_BASE_HPP

#include <cstdlib>

namespace orm {

class ColumnType { // Keep that separate for class slicing
	public:
	size_t length;
	virtual ~ColumnType(){}
	ColumnType(size_t arg_length) : length(arg_length) {}
};

}

#endif

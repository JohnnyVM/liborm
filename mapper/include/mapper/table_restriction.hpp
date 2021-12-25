#ifndef LIBORM_TABLE_RESTRICTION_HPP
#define LIBORM_TABLE_RESTRICTION_HPP

#include <string>

#include "mapper/table_element.hpp"

namespace orm {

	class TableRestriction : public TableElement { // Keep that separate for class slicing
			TableRestriction(const std::string& arg_name) : TableElement(arg_name) {}
	};

}

#endif

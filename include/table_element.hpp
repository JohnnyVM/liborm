#ifndef LIBORM_TABLE_ELEMENT_HPP
#define LIBORM_TABLE_ELEMENT_HPP

#include <string>

namespace orm {

class TableElement { // Keep that separate for class slicing
	public:
	TableElement() = default;
	virtual ~TableElement() = default;
	TableElement(const TableElement&) = delete;
	TableElement& operator=(const TableElement&) = delete;

	/*  */
	const std::string name;

	TableElement(const std::string arg_name) : name(arg_name) {}
};

}

#endif

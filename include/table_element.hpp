#ifndef LIBORM_TABLE_ELEMENT_HPP
#define LIBORM_TABLE_ELEMENT_HPP

#include <string>

namespace orm {

class TableElement { // Keep that separate for class slicing
	public:
	std::string name;
	TableElement(const std::string& arg_name) : name(arg_name) {};
	virtual ~TableElement(){}
};

}

#endif

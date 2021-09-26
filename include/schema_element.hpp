#ifndef LIBORM_SCHEMA_ELEMENT_HPP
#define LIBORM_SCHEMA_ELEMENT_HPP

#include <string>

namespace orm {

class SchemaElement { // Keep that separate for class slicing
	public:
	std::string name;
	SchemaElement(const std::string& arg_name) : name(arg_name) {};
	virtual ~SchemaElement(){}
};

}

#endif


#ifndef LIBORM_SCHEMA_ELEMENT_HPP
#define LIBORM_SCHEMA_ELEMENT_HPP

#include <string>

namespace orm {

class SchemaElement { // Keep that separate for class slicing
	public:
	SchemaElement() {}
	const std::string name;
	SchemaElement(const std::string& arg_name) : name(arg_name) {}
	virtual ~SchemaElement(){}
	virtual SchemaElement* clone() const = 0;
};

}

#endif


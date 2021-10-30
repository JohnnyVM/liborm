#ifndef LIBORM_SCHEMA_ELEMENT_HPP
#define LIBORM_SCHEMA_ELEMENT_HPP

#include <string>

namespace orm {

class SchemaElement { // Keep that separate for class slicing
	public:
	SchemaElement() = default;
	SchemaElement(const SchemaElement&) = delete;
	virtual ~SchemaElement() = default;
	SchemaElement& operator=(const SchemaElement&) = delete;

	const std::string name;
	SchemaElement(const std::string arg_name) : name(arg_name) {}
};

}

#endif


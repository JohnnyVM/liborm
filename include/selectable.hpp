#ifndef LIBORM_SELECTABLE_HPP
#define LIBORM_SELECTABLE_HPP

#include <string>
#include <vector>
#include <memory>

#include "column.hpp"
#include "schema_element.hpp"

namespace orm {

/* Selectable are all elementss that can return */
class Selectable : public SchemaElement { // Keep that separate for class slicing
	public:
	Selectable() : SchemaElement() {}
	Selectable(const std::string& arg_name) : SchemaElement(arg_name) {}
	virtual ~Selectable(){}
	virtual Selectable* clone() const = 0;

	std::vector<std::unique_ptr<orm::Column> >columns;
};

}

#endif

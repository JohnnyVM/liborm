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
	Selectable() = default;
	Selectable(const Selectable&) = delete;
	virtual ~Selectable() = default;
	Selectable& operator=(const Selectable&) = delete;

	std::vector<std::unique_ptr<orm::Column> >columns;
	Selectable(const std::string arg_name) : SchemaElement(arg_name) {}
};

}

#endif

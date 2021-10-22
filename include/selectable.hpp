#ifndef LIBORM_SELECTABLE_HPP
#define LIBORM_SELECTABLE_HPP

#include <string>
#include <vector>
#include <memory>
#include <array>

#include "column.hpp"
#include "schema_element.hpp"
#include "clause_list.hpp"
#include "clause_element.hpp"

namespace orm {

/* Selectable are all elementss that can return */
class Selectable : public SchemaElement { // Keep that separate for class slicing
	public:
	Selectable() = default;
	Selectable(const Selectable&) = delete;
	virtual ~Selectable() = default;
	Selectable& operator=(const Selectable&) = delete;

	std::vector<std::shared_ptr<orm::Column> >c;
	std::vector<orm::ClauseList>clauses; // where is builded with that

	Selectable(const std::string arg_name) : SchemaElement(arg_name) {}

	/* methods */
	Selectable where(orm::ClauseElement);
};

}

#endif

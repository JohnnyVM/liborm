#ifndef LIBORM_MAPPER_TABLE_HPP
#define LIBORM_MAPPER_TABLE_HPP

#include <initializer_list>
#include <vector>
#include <memory>
#include <cassert>

#include "mapper/table_element.hpp"
#include "mapper/table_restriction.hpp"
#include "mapper/schema_element.hpp"
#include "mapper/column.hpp"

namespace orm {

template<class T>
struct movable_il {
    mutable T t;
    operator T() const&& { return std::move(t); }
    movable_il( T&& in ): t(std::move(in)) {}
};

class Table : public orm::SchemaElement {
	public:
	Table& operator=(const Table&) = delete;

	Table(const std::string& arg_name, std::initializer_list<movable_il<std::unique_ptr<orm::Column>> >args) : orm::SchemaElement(arg_name) {
		for(auto&& te : args) {
			std::unique_ptr<orm::Column> elem = std::move(te);
			if(orm::Column* column = dynamic_cast<orm::Column*>(elem.get())) {
				c.push_back(std::make_unique<orm::Column>(
							column->name,
							column->type->clone(),
							column->primary_key,
							column->nullable,
							column->default_value));
			// todo} else if(dynamic_cast<orm::TableRestriction*>(elem.get())) {
				// restrictions.push_back(std::move(elem));
			} else {
				assert(!"Invalid type derived from table element");
			}
		}
	}

	/* Class variables */
	std::vector<std::unique_ptr<orm::Column> >c;
	std::vector<std::unique_ptr<orm::TableRestriction> >restrictions;

	/* Class methods */
};

}

#endif

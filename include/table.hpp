#ifndef LIBORM_TABLE_HPP
#define LIBORM_TABLE_HPP

#include <initializer_list>
#include <vector>
#include <memory>

#include "table_element.hpp"
#include "table_restriction.hpp"
#include "column.hpp"
#include "schema_element.hpp"

namespace orm {

class Table : public SchemaElement {
	public:
	std::vector<std::unique_ptr<orm::Column> >columns;
	std::vector<std::unique_ptr<orm::TableRestriction> >restrictions;

	Table(const std::string& name, std::initializer_list<TableElement*>args);

	Table* clone() const override;
	Table(const Table&) : SchemaElement() {};
};

}

#endif


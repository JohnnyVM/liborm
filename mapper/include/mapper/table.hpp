#ifndef LIBORM_MAPPER_TABLE_HPP
#define LIBORM_MAPPER_TABLE_HPP

#include <initializer_list>
#include <vector>
#include <memory>

#include "mapper/table_element.hpp"
#include "mapper/table_restriction.hpp"
#include "mapper/schema_element.hpp"

namespace orm {

class Insert;
class Column;

class Table : public orm::SchemaElement {
	public:
	Table& operator=(const Table&) = delete;
	Table(const std::string& name, std::initializer_list<std::shared_ptr<TableElement> >args);

	/* Class variables */
	std::vector<std::shared_ptr<orm::Column> >c;
	std::vector<std::shared_ptr<orm::TableRestriction> >restrictions;

	/* Class methods */
};

}

#endif

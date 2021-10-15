#ifndef LIBORM_TABLE_HPP
#define LIBORM_TABLE_HPP

#include <initializer_list>
#include <vector>
#include <memory>

#include "owner.hpp"
#include "selectable.hpp"
#include "table_element.hpp"
#include "table_restriction.hpp"
#include "column.hpp"
#include "schema_element.hpp"
#include "insert.hpp"

namespace orm {

class Table : public Selectable {
	public:
	Table() = default;
	virtual ~Table() = default;
	Table& operator=(const Table&) = delete;

	/* Class variables */
	std::vector<std::shared_ptr<orm::TableRestriction> >restrictions;

	/* Class methods */
	Table(const std::string& name, std::initializer_list<std::shared_ptr<TableElement> >args);

	orm::Insert insert();
};

}

#endif


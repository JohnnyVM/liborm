#include <cassert>
#include <initializer_list>
#include <memory>
#include <string>
#include <typeinfo>
#include <type_traits>

#include "mapper/column.hpp"
#include "mapper/table.hpp"
#include "mapper/table_restriction.hpp"

orm::Table::Table(const std::string& arg_name, std::initializer_list<std::shared_ptr<TableElement> >args) : orm::SchemaElement(arg_name) {

	for(std::shared_ptr<TableElement> te : args) {
		if(typeid(*te) == typeid(orm::Column)) {
			std::static_pointer_cast<orm::Column>(te)->table_parent = this;
			c.push_back(std::shared_ptr<orm::Column>(std::static_pointer_cast<orm::Column>(te)));
		} else if(typeid(*te) == typeid(orm::TableRestriction)) {
			restrictions.push_back(std::shared_ptr<orm::TableRestriction>(std::static_pointer_cast<orm::TableRestriction>(te)));
		} else {
			throw std::invalid_argument("Invalid element pass to table constructor");
		}
	}
}


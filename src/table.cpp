#include <cassert>
#include <initializer_list>
#include <memory>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>

#include "column.hpp"
#include "table.hpp"
#include "table_restriction.hpp"
#include "schema_element.hpp"

orm::Table::Table(const std::string& name_arg, std::initializer_list<TableElement*>args)
	: orm::SchemaElement(name_arg) {

	for(TableElement* te : args) {
		// \warning push_back can throw: if this happen a memory leak will happen, its not acceptable
		// not handle that throw NEVER, let the program die
		if(typeid(*te) == typeid(orm::Column)) {
			columns.push_back(std::unique_ptr<orm::Column>(dynamic_cast<orm::Column*>(te)));
		} else if(typeid(*te) == typeid(orm::TableRestriction)) {
			restrictions.push_back(std::unique_ptr<orm::TableRestriction>(dynamic_cast<orm::TableRestriction*>(te)));
		} else {
			// Same should not happen and then should not be handled
			throw std::invalid_argument("Invalid element pass to table constructor");
		}
	}
}

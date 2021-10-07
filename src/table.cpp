#include <cassert>
#include <initializer_list>
#include <memory>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>

#include "selectable.hpp"
#include "owner.hpp"
#include "column.hpp"
#include "table.hpp"
#include "table_restriction.hpp"

orm::Table::Table(const std::string& arg_name, std::initializer_list<TableElement*>args) : orm::Selectable(arg_name) {

	for(TableElement* te : args) {
  	// \warning push_back can throw: if this happen a memory leak will happen, its not acceptable
  	// not handle that throw NEVER, let the program die
		if(typeid(*te) == typeid(orm::Column)) {
			orm::Column* c = static_cast<orm::Column*>(te);
			columns.push_back(std::unique_ptr<orm::Column>(c));
		} else if(typeid(*te) == typeid(orm::TableRestriction)) {
			orm::TableRestriction* r = static_cast<orm::TableRestriction*>(te);
			restrictions.push_back(std::unique_ptr<orm::TableRestriction>(r));
		} else {
  		// Same should not happen and then should not be handled
			throw std::invalid_argument("Invalid element pass to table constructor");
		}
	}
}


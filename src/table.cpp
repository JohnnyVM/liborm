#include <cassert>
#include <initializer_list>
#include <memory>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>

#include "insert.hpp"
#include "selectable.hpp"
#include "owner.hpp"
#include "column.hpp"
#include "table.hpp"
#include "table_restriction.hpp"
#include "insert.hpp"

orm::Table::Table(const std::string& arg_name, std::initializer_list<std::shared_ptr<TableElement> >args) : orm::Selectable(arg_name) {

	for(std::shared_ptr<TableElement> te : args) {
  	// \warning push_back can throw: if this happen a memory leak will happen, its not acceptable
  	// not handle that throw NEVER, let the program die
		if(typeid(*te) == typeid(orm::Column)) {
			columns.push_back(std::shared_ptr<orm::Column>(std::static_pointer_cast<orm::Column>(te)));
		} else if(typeid(*te) == typeid(orm::TableRestriction)) {
			restrictions.push_back(std::shared_ptr<orm::TableRestriction>(std::static_pointer_cast<orm::TableRestriction>(te)));
		} else {
  		// Same should not happen and then should not be handled
			throw std::invalid_argument("Invalid element pass to table constructor");
		}
	}
}

orm::Insert orm::Table::insert() {
	orm::Insert insert(this);

	return insert;
}


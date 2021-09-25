#ifndef LIBORM_TABLE_HPP
#define LIBORM_TABLE_HPP

#include <initializer_list>
#include <vector>
#include <memory>
#include <map>

#include "table_element.hpp"
#include "column.hpp"

namespace orm {

class Table : public SchemaElement {
	public:
	template <class ...ArgTypes>
	Table(std::string name, ArgTypes... args) : Table(name, {args...}) {}

	//orm::Column operator[](const std::string& name);
	//std::map<owner<orm::TableElement*> >columns;
	std::map<std::unique_ptr<orm::TableElement> >columns;

	private:
	Table(const std::string& name, std::initializer_list<TableElement*>args);
};

}

#endif


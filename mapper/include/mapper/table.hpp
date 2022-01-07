#ifndef LIBORM_MAPPER_TABLE_HPP
#define LIBORM_MAPPER_TABLE_HPP

#include <initializer_list>
#include <vector>
#include <memory>

#include "mapper/table_element.hpp"
#include "mapper/table_restriction.hpp"
#include "mapper/schema_element.hpp"
#include "mapper/column.hpp"

namespace orm {

class Column;

template<class T>
struct movable_il {
    mutable T t;
    operator T() const&& { return std::move(t); }
    movable_il( T&& in ): t(std::move(in)) {}
};

template<class T, class A=std::allocator<T>>
std::vector<T,A> vector_from_il( std::initializer_list< movable_il<T> > il ) {
    std::vector<T,A> r( std::make_move_iterator(il.begin()), std::make_move_iterator(il.end()) );
    return r;
}

class Table : public orm::SchemaElement {
	public:
	Table& operator=(const Table&) = delete;

	Table(const std::string& arg_name, std::initializer_list<movable_il<TableElement> >args) : orm::SchemaElement(arg_name) {
		for(auto&& te : args) {
			if(typeid(te) == typeid(orm::Column)) {
				c.push_back(te);
			} else if(typeid(*te) == typeid(orm::TableRestriction)) {
				restrictions.push_back(te);
			} else {
				throw std::invalid_argument("Invalid element pass to table constructor");
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

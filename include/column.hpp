#ifndef LIBORM_COLUMN_HPP
#define LIBORM_COLUMN_HPP

#include <typeinfo>
#include <cstdint>
#include <string>
#include <utility>
#include <memory>
#include <assert.h>

#include "table_element.hpp"
#include "schema_element.hpp"
#include "column/base.hpp"
#include "expresion.hpp"
#include "table.hpp"

namespace orm { namespace column_value {
union type { std::uintmax_t INTEGER; std::string VARCHAR; };
}}

namespace orm {

/**
 * \brief necesary definition to pass to class constructor
 */
struct column_params {
	const std::string& name;
	orm::ColumnType* type;
	bool primary_key;
	bool nullable;
	std::pair<orm::column_value::type, std::type_info&>(*default_value)(void);
};

/**
 * \brief
 */
class Column : public orm::TableElement {
	public:
	Column(const Column&) : TableElement() {};
	~Column() override {}
	std::unique_ptr<orm::ColumnType> type;
	bool primary_key = false;
	bool nullable = true;
	/// \todo C17 variant return the value type with holds_alternative
	std::pair<orm::column_value::type, std::type_info&>(*default_value)(void); /* \todo */

	explicit operator const std::string(); // \todo remove this
	orm::Table* table_parent = nullptr; // used for recognice the parent table since the constructor

	explicit Column(column_params p)
		: TableElement(p.name),
		type(p.type),
		primary_key(p.primary_key),
		nullable(p.nullable),
		default_value(p.default_value){ assert(primary_key!=true || nullable == false); };

	/** method like form where claused */
	//orm::Expresion like(std::string value);

	private:
	//orm::Expresion compare(std::string optr, std::string value);

};

/** Return a class Column */
std::shared_ptr<Column> column(column_params p);

}

#endif

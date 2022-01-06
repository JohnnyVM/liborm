#ifndef LIBORM_MAPPER_COLUMN_HPP
#define LIBORM_MAPPER_COLUMN_HPP

#include <type_traits>
#include <cstdint>
#include <string>
#include <variant>
#include <cassert>
#include <memory>

#include "mapper/table_element.hpp"
#include "type/engine.h"
#include "type/types.hpp"
#include "mapper/table.hpp"

namespace orm {

using default_type = std::variant<
	type::String,
	type::Numeric,
	type::Datetime>;

struct column_params {
	const std::string& name;
	std::unique_ptr<TypeEngine> type;
	bool primary_key;
	bool nullable;
	default_type(*default_value)(void);
};

/**
 * \brief necesary definition to pass to class constructor
 */
class Column : public orm::TableElement {
	public:
	Column(const Column&) : TableElement() {};
	~Column() {}
	Column(column_params p)
		: TableElement(p.name),
		type(p.type),
		primary_key(p.primary_key),
		nullable(p.nullable),
		default_value(p.default_value)
	{assert(primary_key!=true || nullable == false);}
	std::unique_ptr<TypeEngine> type;
	bool primary_key = false;
	bool nullable = true;
	default_type(*default_value)(void); /* \todo */
};

/** Return a class Column */
std::unique_ptr<Column> column(column_params p);

}

#endif

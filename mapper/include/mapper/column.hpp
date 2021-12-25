#ifndef LIBORM_MAPPER_COLUMN_HPP
#define LIBORM_MAPPER_COLUMN_HPP

#include <typeinfo>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <variant>

#include "mapper/table_element.hpp"
#include "type/engine.h"
#include "mapper/table.hpp"

namespace orm {

/**
 * \brief necesary definition to pass to class constructor
 */
struct column_params {
	const std::string& name;
	TypeEngine* type;
	bool primary_key;
	bool nullable;
	void*(*default_value)(void);
};

/**
 * \brief
 */
class Column : public orm::TableElement {
	public:
	Column(const Column&) : TableElement() {};
	~Column() override {}
	std::unique_ptr<TypeEngine> type;
	bool primary_key = false;
	bool nullable = true;
	/// \todo C17 variant return the value type with holds_alternative
	void*(*default_value)(void); /* \todo */

	orm::Table* table_parent = nullptr; // used for recognice the parent table since the constructor

	explicit Column(column_params p)
		: TableElement(p.name),
		type(p.type),
		primary_key(p.primary_key),
		nullable(p.nullable),
		default_value(p.default_value){
			if(primary_key!=true || nullable == false) {
				std::logic_error("Nullable primary key");
			}
		};
};

/** Return a class Column */
std::shared_ptr<Column> column(column_params p);

}

#endif

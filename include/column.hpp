#ifndef LIBORM_COLUMN_HPP
#define LIBORM_COLUMN_HPP

#include <typeinfo>
#include <cstdint>
#include <string>
#include <utility>

#include "table_element.hpp"
#include "schema_element.hpp"

namespace orm { namespace column {
union default_value_type { std::uintmax_t INTEGER; std::string VARCHAR; };
}}

namespace orm {

class Column : public TableElement {
	private:
		struct params {
			const std::string& name;
			bool primary_key;
			bool nullable;
			std::pair<orm::column::default_value_type, std::type_info&>(*default_value)(void);
		};

	public:
	bool primary_key;
	bool nullable;
	/// \todo C17 variant return the value type with holds_alternative
	std::pair<orm::column::default_value_type, std::type_info&>(*default_value)(void); /* unused */

	explicit Column(params p)
		: TableElement(p.name),
		primary_key(p.primary_key),
		nullable(p.nullable),
		default_value(p.default_value){};
};

}

#endif

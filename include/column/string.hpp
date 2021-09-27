#ifndef LIBORM_COLUMN_VARCHAR_HPP
#define LIBORM_COLUMN_VARCHAR_HPP

#include <string>
#include <cstdint>

#include "column/base.hpp"

namespace orm {

// https://docs.sqlalchemy.org/en/14/core/type_basics.html
class String : public orm::ColumnType { // Keep that separate for class slicing
	public:
	const std::string display_name;
	String(size_t arg_length) :
		orm::ColumnType(minimun_is_1(arg_length)),
		display_name(init_display_name(minimun_is_1(arg_length))) {}
	explicit operator const std::string() override { return display_name; };

	private:
	static std::string init_display_name(size_t length) {
		return "character varying(" + std::to_string(length) + ")";
	}
	static size_t minimun_is_1(size_t len) { return len >= 1 ? len : 1; }
};

}

#endif



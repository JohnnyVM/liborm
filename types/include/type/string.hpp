#ifndef LIBORM_COLUMN_VARCHAR_HPP
#define LIBORM_COLUMN_VARCHAR_HPP

#include <string>
#include <cstdint>

#include "type/engine.hpp"

namespace orm::type {

// https://docs.sqlalchemy.org/en/14/core/type_basics.html
class String : public orm::TypeEngine { // Keep that separate for class slicing
	public:
	String(size_t arg_length) :
		orm::TypeEngine(init_name(minimun_is_1(arg_length)), minimun_is_1(arg_length)) {}

	private:
	inline static std::string init_name(size_t length) {
		return "character varying(" + std::to_string(length) + ")";
	}
	inline static size_t minimun_is_1(size_t len) { return len >= 1 ? len : 1; }
};

}

#endif


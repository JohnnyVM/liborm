#ifndef LIBORM_COLUMN_NUMBER_HPP
#define LIBORM_COLUMN_NUMBER_HPP

#include <cassert>
#include <decimal/decimal>
#include <limits>
#include <string>
#include <cstdint>
#include <type_traits>

#include "type/engine.h"

namespace orm::type {

class Numeric : virtual public TypeEngine { // Keep that separate for class slicing
	public:
	Numeric(unsigned arg_precision, unsigned arg_scale, std::decimal::decimal128 arg_value) :
		TypeEngine(init_name(arg_precision, arg_scale), sizeof(std::decimal::decimal128)),
		precision(arg_precision), scale(arg_scale), _value(arg_value) {
			assert(precision <= std::numeric_limits<std::decimal::decimal128>::digits10);
		}
	Numeric(unsigned arg_precision, unsigned arg_scale) :
		TypeEngine(init_name(arg_precision, arg_scale), sizeof(std::decimal::decimal128)),
		precision(arg_precision), scale(arg_scale) {
			assert(precision <= std::numeric_limits<std::decimal::decimal128>::digits10);
		}

	const unsigned precision;
	const unsigned scale;

	private:
	std::decimal::decimal128 _value;
	static std::string init_name(unsigned p, unsigned s) {
		return (std::string)"number(" + std::to_string(p) + "," + std::to_string(s) + ")";
	}
};

}

#endif



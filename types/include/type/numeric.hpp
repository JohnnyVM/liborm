#ifndef LIBORM_COLUMN_NUMBER_HPP
#define LIBORM_COLUMN_NUMBER_HPP

#include <cassert>
#include <decimal/decimal>
#include <string>
#include <cstdint>
#include <type_traits>

#define __STDC_WANT_DEC_FP__
#include <float.h>

#include "type/engine.hpp"

namespace orm::type {

class Numeric : virtual public orm::TypeEngine {
	public:
	template<typename W,
			 std::enable_if_t<std::is_arithmetic<W>::value, bool> = true
	>
	Numeric(unsigned arg_precision, unsigned arg_scale, W arg_value) : Numeric(arg_precision, arg_scale, (std::decimal::decimal128)arg_value) {}

	Numeric(unsigned arg_precision, unsigned arg_scale, std::decimal::decimal128 arg_value) :
		orm::TypeEngine(init_name(arg_precision, arg_scale), sizeof(std::decimal::decimal128)),
		precision(arg_precision), scale(arg_scale), _value(arg_value) {
			assert(precision <= DEC128_MANT_DIG);
		}
	Numeric(unsigned arg_precision, unsigned arg_scale) :
		orm::TypeEngine(init_name(arg_precision, arg_scale), sizeof(std::decimal::decimal128)),
		precision(arg_precision), scale(arg_scale) {
			assert(precision <= DEC128_MANT_DIG);
		}

	const unsigned precision;
	const unsigned scale;

	/**
	 * \brief cast to arithmetic (int, float, etc) marked as implicit as reminder you are losing precision
	 * \warning you lost the decimal part
	 * \tparam T output type cast
	 * \return T returning value of type \p T
	 */
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
	inline explicit operator T() const { return (T)std::decimal::decimal_to_long_long(_value); }

	template<typename U, std::enable_if_t<std::is_integral<U>::value, bool> = true>
	inline friend bool operator==(const Numeric& lhs, const U& rhs) {return lhs._value == std::decimal::decimal128(rhs);}
	// todo float point have to be equal until the precision
	template<typename X>
	inline friend bool operator==(const X& lhs, const Numeric& rhs) { return rhs == lhs; }
	template<typename V>
	inline friend bool operator!=(const Numeric& lhs, const V& rhs) { return !(lhs == rhs); } // remove in C++20
	template<typename Y>
	inline friend bool operator!=(const Y& lhs, const Numeric& rhs) { return !(rhs == lhs); } // remove in C++20
	/** \todo ... */

	private:
	std::decimal::decimal128 _value;
	inline static std::string init_name(unsigned p, unsigned s) {
		return (std::string)"number(" + std::to_string(p) + "," + std::to_string(s) + ")";
	}
};

}

#endif



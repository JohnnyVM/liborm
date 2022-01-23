#ifndef LIBORM_COLUMN_NUMBER_HPP
#define LIBORM_COLUMN_NUMBER_HPP

#include <cassert>
#include <stdexcept>
#include <decimal/decimal>
#include <string>
#include <cstdint>
#include <type_traits>
#include <limits>
#include <memory>

#include "liborm/type/engine.h"
#include "liborm/type/integer.hpp"
#define __STDC_WANT_DEC_FP__
#include <cfloat>

namespace orm::type {

/**
 * \brief Numeric class especialization
 * \warning floating point arithmetic/operators are not defined
 * 
 */
class Numeric : virtual public TypeEngine {
	public:
	template<typename A,
			 std::enable_if_t<std::is_integral<A>::value and std::is_unsigned<A>::value, bool> = true,
			 typename B,
			 std::enable_if_t<std::is_integral<B>::value and std::is_unsigned<B>::value, bool> = true>
	Numeric(const A& arg_precision, const B& arg_scale, std::decimal::decimal128 arg_value) :
		TypeEngine(init_name(arg_precision, arg_scale), typeid(*this), sizeof(std::decimal::decimal128)),
		precision(arg_precision), scale(arg_scale), _value(arg_value) {
			assert(precision <= DEC128_MANT_DIG);}

	template<typename A,
			 std::enable_if_t<std::is_integral<A>::value and std::is_unsigned<A>::value, bool> = true,
			 typename B,
			 std::enable_if_t<std::is_integral<B>::value and std::is_unsigned<B>::value, bool> = true,
			 typename W,
			 std::enable_if_t<std::is_arithmetic<W>::value, bool> = true>
	Numeric(const A& arg_precision, const B& arg_scale, W arg_value) :
	Numeric(arg_precision, arg_scale, (std::decimal::decimal128)arg_value) {
		assert(not(std::is_floating_point<W>::value ^ (scale > 0)));}

	template<typename A,
			 std::enable_if_t<std::is_integral<A>::value and std::is_unsigned<A>::value, bool> = true,
			 typename B,
			 std::enable_if_t<std::is_integral<B>::value and std::is_unsigned<B>::value, bool> = true>
	Numeric(const A& arg_precision, const B& arg_scale) :
		TypeEngine(init_name(arg_precision, arg_scale), typeid(*this), sizeof(std::decimal::decimal128)), precision(arg_precision), scale(arg_scale) {
			assert(precision <= DEC128_MANT_DIG);}

	template<typename A,
			 std::enable_if_t<std::is_integral<A>::value and std::is_unsigned<A>::value, bool> = true>
	Numeric(const A& arg_precision) : Numeric(arg_precision, 0U) {}

	Numeric(const Numeric& other) : Numeric(other.precision, other.scale, other._value) {}

	std::unique_ptr<TypeEngine> clone() const { return std::make_unique<Numeric>(precision, scale, _value); }

	template<typename I, std::enable_if_t<std::is_integral<I>::value, bool> = true>
	inline explicit operator I() const {
		assert(_value < std::numeric_limits<I>::lowest() || std::numeric_limits<I>::max() > _value); // overflow
		return is_null ? (I)0 : (I)std::decimal::decimal128_to_long_long(_value); }
	inline explicit operator long double() const {
		assert(_value < (std::decimal::decimal128)std::numeric_limits<long double>::lowest() || (std::decimal::decimal128)std::numeric_limits<long double>::max() > _value); // overflow
		return is_null ? 0 : std::decimal::decimal128_to_long_double(_value); }
	inline explicit operator double() const {
		assert(_value < (std::decimal::decimal128)std::numeric_limits<double>::lowest() || (std::decimal::decimal128)std::numeric_limits<double>::max() > _value); // overflow
		return is_null ? 0 : std::decimal::decimal128_to_double(_value); }
	inline explicit operator float() const {
		assert(_value < (std::decimal::decimal128)std::numeric_limits<float>::lowest() || (std::decimal::decimal128)std::numeric_limits<float>::max() > _value); // overflow
		return is_null ? 0 : std::decimal::decimal128_to_float(_value); }
	inline explicit operator std::decimal::decimal128() const { return is_null ? 0 : _value; }
	inline explicit operator std::decimal::decimal64() const { return is_null ? 0 : std::decimal::decimal64(_value); }
	inline explicit operator std::decimal::decimal32() const { return is_null ? 0 : std::decimal::decimal32(_value); }

	inline bool operator!() const { return this->is_null ? false : this->_value == 0;}

	/**
	 * \brief Comparations between numeric
	 * \todo flaoting point operations
	 * \param lhs left operator
	 * \param rhs right oeprator
	 * \return true if are equal
	 * \return false if not are equal
	 */
#define _DECLARE_TYPE_NUMERIC_COMPARISON(_Op) \
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>\
	inline friend bool operator _Op(const Numeric& __lhs, const T& __rhs) {return __lhs.is_null ? false : __lhs._value _Op __rhs;}\
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>\
	inline friend bool operator _Op(const T& __lhs, const Numeric& __rhs) {return __rhs.is_null ? false : __lhs _Op __rhs._value;}\
	inline friend bool operator _Op(const Numeric& __lhs, const Numeric& __rhs) {return __lhs.is_null or __rhs.is_null ? false : __lhs._value _Op __rhs._value;}\
	inline friend bool operator _Op(const Numeric& __lhs, const std::decimal::decimal128& __rhs) {return __lhs.is_null ? false : __lhs._value _Op __rhs;}\
	inline friend bool operator _Op(std::decimal::decimal128 __lhs, const Numeric& __rhs) {return __rhs.is_null ? false : __lhs _Op __rhs._value;}\
	inline friend bool operator _Op(const Numeric& __lhs, const std::decimal::decimal64& __rhs) {return __lhs.is_null ? false : __lhs._value _Op __rhs;}\
	inline friend bool operator _Op(std::decimal::decimal64 __lhs, const Numeric& __rhs) {return __rhs.is_null ? false : __lhs _Op __rhs._value;}\
	inline friend bool operator _Op(const Numeric& __lhs, std::decimal::decimal32 __rhs) {return __lhs.is_null ? false : __lhs._value _Op __rhs;}\
	inline friend bool operator _Op(std::decimal::decimal32 __lhs, const Numeric& __rhs) {return __rhs.is_null ? false : __lhs _Op __rhs._value;}
	_DECLARE_TYPE_NUMERIC_COMPARISON(==)
	_DECLARE_TYPE_NUMERIC_COMPARISON(!=)
	_DECLARE_TYPE_NUMERIC_COMPARISON(>)
	_DECLARE_TYPE_NUMERIC_COMPARISON(<)
	_DECLARE_TYPE_NUMERIC_COMPARISON(>=)
	_DECLARE_TYPE_NUMERIC_COMPARISON(<=)
/// \todo define comparaision with floating point

/// \todo operations with null values???
#define _DECLARE_TYPE_NUMERIC_BINARY_OP_WITH_INT(_Op) \
	inline Numeric& operator _Op##=(const Numeric& rhs) { is_null = false; _value _Op##= rhs._value; return *this;}\
	inline friend Numeric operator _Op(Numeric lhs, const Numeric& rhs) { lhs _Op##= rhs; return lhs;}\
	inline Numeric& operator _Op##=(const std::decimal::decimal128& rhs) { is_null = false; _value _Op##= rhs; return *this;}\
	inline friend Numeric operator _Op(Numeric lhs, const std::decimal::decimal128& rhs) { lhs _Op##= rhs; return lhs;}\
	inline Numeric& operator _Op##=(const std::decimal::decimal64& rhs) { is_null = false; _value _Op##= rhs; return *this;};\
	inline friend Numeric operator _Op(Numeric lhs, const std::decimal::decimal64& rhs) { lhs _Op##= rhs; return lhs;}\
	inline Numeric& operator _Op##=(const std::decimal::decimal32& rhs) { is_null = false; _value _Op##= rhs; return *this;};\
	inline friend Numeric operator _Op(Numeric lhs, const std::decimal::decimal32& rhs) { lhs _Op##= rhs; return lhs;}\
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>\
	inline Numeric& operator _Op##=(const T& rhs) { is_null = false; _value _Op##= rhs; return *this;}\
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>\
	inline friend Numeric operator _Op(Numeric lhs, const T& rhs) { lhs _Op##= rhs; return lhs;}
	_DECLARE_TYPE_NUMERIC_BINARY_OP_WITH_INT(+)
	_DECLARE_TYPE_NUMERIC_BINARY_OP_WITH_INT(-)
	_DECLARE_TYPE_NUMERIC_BINARY_OP_WITH_INT(*)
	_DECLARE_TYPE_NUMERIC_BINARY_OP_WITH_INT(/)

	template<typename TID, std::enable_if_t<std::is_integral<TID>::value, bool> = true>
	inline Numeric& operator=(const TID& rhs) { is_null = false; _value = rhs; return *this;};
	inline Numeric& operator=(const std::decimal::decimal128& rhs) { is_null = false; _value = rhs; return *this; }
	inline Numeric& operator=(const std::decimal::decimal64& rhs) { is_null = false; _value = rhs; return *this; }
	inline Numeric& operator=(const std::decimal::decimal32& rhs) { is_null = false; _value = rhs; return *this; }

	/**
	 * \brief Output the number as string
	 * \warning if the output is truncated throw, if you want be sure not throw do a explicit cast before
	 * \todo use a byte correct cast
	 * \return std::string 
	 */
	explicit operator std::string() const;

	const unsigned precision;
	const unsigned scale;

	private:
	std::decimal::decimal128 _value;
	inline static std::string init_name(unsigned p, unsigned s) {
		return (std::string)"number(" + std::to_string(p) + "," + std::to_string(s) + ")";
	}
};

}

namespace orm {

std::unique_ptr<TypeEngine> Numeric(unsigned precision);
std::unique_ptr<TypeEngine> Numeric(unsigned precision, unsigned scale);

}

#endif



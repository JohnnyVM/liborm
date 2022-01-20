#ifndef LIBORM_TYPE_INTEGER_HPP
#define LIBORM_TYPE_INTEGER_HPP

#include <memory>
#include <limits>
#include <type_traits>
#include <string>

#include <stdint.h>
#include "liborm/type/engine.h"

namespace orm::type {

class Integer : public TypeEngine {
	public:
	Integer() : TypeEngine("integer", typeid(*this), sizeof(intmax_t)) {}
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
	Integer(T val) : TypeEngine("integer", typeid(*this), sizeof(intmax_t)), _value(val) {
		assert(val < std::numeric_limits<intmax_t>::lowest() || std::numeric_limits<intmax_t>::max() > val); // overflow
	}

	explicit operator std::string() const override { return std::to_string(_value); };
	std::unique_ptr<TypeEngine> clone() const override { return std::make_unique<Integer>(_value); }

	template<typename I, std::enable_if_t<std::is_arithmetic<I>::value, bool> = true>
	inline explicit operator I() const {
		if(is_null) {
			return (I)0;
		}
		assert(_value < std::numeric_limits<I>::lowest() || std::numeric_limits<I>::max() > _value); // overflow
		return (I)_value; }



	private:
	intmax_t _value;
};

}

#endif

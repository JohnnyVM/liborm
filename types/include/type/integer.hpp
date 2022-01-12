#ifndef LIBORM_TYPE_INTEGER_HPP
#define LIBORM_TYPE_INTEGER_HPP

#include <memory>
#include <limits>
#include <type_traits>

#include <stdint.h>
#include "type/engine.h"

namespace orm::type {

class Integer : public TypeEngine {
	public:
	Integer() : TypeEngine("integer", typeid(*this), sizeof(intmax_t)) {}
	template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
	Integer(T val) : TypeEngine("integer", typeid(*this), sizeof(intmax_t)), _value(val) {
		assert(val < std::numeric_limits<uintmax_t>::lowest() || std::numeric_limits<uintmax_t>::max() > val); // overflow
	}

	//std::unique_ptr<TypeEngine> clone() const { return std::make_unique<Integer>(_value); }

	private:
	intmax_t _value;
};

}

#endif

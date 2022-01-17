#ifndef LIBORM_TYPE_NULL_HPP
#define LIBORM_TYPE_NULL_HPP

#include "liborm/type/engine.h"

#include <string>

namespace orm::type {

class Null : public virtual TypeEngine {
	public:
	~Null() = default;
	Null() noexcept : TypeEngine(std::string(), typeid(*this), 0) {
        is_null = true;
    }

	std::unique_ptr<TypeEngine> clone() const override { return std::make_unique<Null>(); }

    explicit operator std::string() const { return std::string(); };
	inline bool operator!() const { return false ; }

#define _BINARY_COMP_OP(_Op) \
    template<typename T> \
    inline friend bool operator _Op(const Null& _lhs, const T& _rhs) { return false; } \
    template<typename T> \
    inline friend bool operator _Op(const T& _lhs, const Null& _rhs) { return false; }
_BINARY_COMP_OP(==)
_BINARY_COMP_OP(>=)
_BINARY_COMP_OP(<=)
_BINARY_COMP_OP(!=)
_BINARY_COMP_OP(>)
_BINARY_COMP_OP(<)

};

}

#endif
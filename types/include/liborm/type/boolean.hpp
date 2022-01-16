#ifndef LIBORM_TYPE_BOOLEAN_HPP
#define LIBORM_TYPE_BOOLEAN_HPP

#include <memory>

#include "liborm/type/engine.h"

namespace orm::type {

class Boolean : public virtual TypeEngine {
	public:
	Boolean() : TypeEngine("boolean", typeid(*this), sizeof(bool)) {}
	Boolean(bool arg) : TypeEngine("boolean", typeid(*this), sizeof(bool)), _value(arg) {}
	//std::unique_ptr<TypeEngine> clone() const { return std::make_unique<Boolean>(_value); }
	private:
	bool _value;
};

}

#endif

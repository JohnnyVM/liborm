#ifndef LIBORM_TYPE_BOOLEAN_HPP
#define LIBORM_TYPE_BOOLEAN_HPP

#include "type/engine.hpp"

namespace orm::type {

class Boolean : public TypeEngine {
	public:
	Boolean() : TypeEngine("boolean", sizeof(bool)) {}
};

}

#endif
#ifndef LIBORM_TYPE_BOOLEAN_HPP
#define LIBORM_TYPE_BOOLEAN_HPP

#include "type/engine.hpp"

namespace orm::type {

class Boolean : public virtual orm::TypeEngine {
	public:
	Boolean() : orm::TypeEngine("boolean", sizeof(bool)) {}
};

}

#endif
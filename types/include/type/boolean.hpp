#ifndef LIBORM_TYPE_BOOLEAN_HPP
#define LIBORM_TYPE_BOOLEAN_HPP

#include "type/engine.h"

namespace orm::type {

class Boolean : public virtual TypeEngine {
	public:
	Boolean() : TypeEngine("boolean", sizeof(bool)) {}
};

}

#endif
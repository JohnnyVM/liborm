#ifndef LIBORM_TYPE_INTEGER_HPP
#define LIBORM_TYPE_INTEGER_HPP

#include "type/engine.hpp"

namespace orm::type {

class Integer : public TypeEngine {
	public:
	Integer() : TypeEngine("integer", sizeof(intmax_t)) {}
};

}

#endif

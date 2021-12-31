#ifndef LIBORM_TYPE_FLOAT_HPP
#define LIBORM_TYPE_FLOAT_HPP

#include "type/engine.hpp"

namespace orm::type {

/**
 * \brief represent IEEE Standard 754 for Binary Floating-Point Arithmetic
 * 
 * basically the diference with numeric is that this is a 64 bits base 2
 */
class Float : public virtual TypeEngine {
	public:
	Float() : TypeEngine("float", sizeof(long double)) {}
};

}

#endif
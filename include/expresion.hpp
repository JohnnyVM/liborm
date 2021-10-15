#ifndef LIBORM_EXPRESION_HPP
#define LIBORM_EXPRESION_HPP

#include <string>

#include "selectable.hpp"

namespace orm {

class Expresion {
	public:
	Expresion() = default;
	virtual ~Expresion() = default;

	virtual operator const std::string() = 0;
};

}

#endif


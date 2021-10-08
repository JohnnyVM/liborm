#ifndef LIBORM_EXPRESION_HPP
#define LIBORM_EXPRESION_HPP

#include <string>

#include "selectable.hpp"

namespace orm {

class Expresion {
	public:
	Expresion() = default;
	Expresion(const Expresion&) = delete;
	virtual ~Expresion() = default;
	Expresion& operator=(const Expresion&) = delete;

	virtual operator const std::string() = 0;
};

}

#endif


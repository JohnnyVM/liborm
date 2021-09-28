#ifndef LIBORM_EXPRESION_HPP
#define LIBORM_EXPRESION_HPP

#include <string>

#include "table.hpp"

namespace orm {

class Expresion {
	public:
	virtual explicit operator const std::string() = 0;
	Expresion(orm::Selectable* el) : selectable(el->clone()){}
	protected:
	std::unique_ptr<orm::Selectable>selectable;
};

}

#endif


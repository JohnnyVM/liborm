#ifndef LIBORM_CLAUSE_ELEMENT_HPP
#define LIBORM_CLAUSE_ELEMENT_HPP

#include <string>
#include <memory>

#include "expresion.hpp"
#include "expresion.hpp"

namespace orm {

class ClauseElement : public orm::Expresion {
	public:
	virtual operator const std::string() = 0;
};

}

#endif


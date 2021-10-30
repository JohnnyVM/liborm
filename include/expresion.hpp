#ifndef LIBORM_EXPRESION_HPP
#define LIBORM_EXPRESION_HPP

#include <string>
#include <vector>

#include "engine.hpp"

namespace orm {

class Expresion {
	public:
	Expresion() = default;
	virtual ~Expresion() = default;

	virtual operator const std::string() = 0;

	/**
	 * \brief for compile a expresion against a dialect (oracle/postgres/sqlite)
	 * \todo define this
	 */
	//virtual std::string compile(orm::Engine* engine) = 0;
};

}

#endif


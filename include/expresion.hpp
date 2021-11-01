#ifndef LIBORM_EXPRESION_HPP
#define LIBORM_EXPRESION_HPP

#include <string>
#include <vector>

#include "engine.hpp"
#include "compiled.hpp"

namespace orm {

class Expresion {
	public:
	Expresion() = default;
	virtual ~Expresion() = default;

	/**
	 * \brief for compile a expresion against a dialect (oracle/postgres/sqlite)
	 * \todo define this
	 */
	virtual orm::Compiled compile(std::string dialect) { return orm::Compiled(); };
	virtual orm::Compiled compile(orm::Engine* engine) { return orm::Compiled(); };
};

}

#endif


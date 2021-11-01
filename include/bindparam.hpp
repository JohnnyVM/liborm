#ifndef LIBORM_BINDPARAM_HPP
#define LIBORM_BINDPARAM_HPP

#include <string>

#include "expresion.hpp"

namespace orm {

/**
 * \brief base class as group of ClauseElements
 */
class BindParam : orm::Expresion {
	public:
	const std::string name;
	BindParam(const std::string &arg_name) : name(arg_name) {}
};

/** \brief mirror function for build the class */
BindParam bindparam(std::string);

}

#endif


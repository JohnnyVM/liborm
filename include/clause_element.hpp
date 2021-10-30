#ifndef LIBORM_CLAUSE_ELEMENT_HPP
#define LIBORM_CLAUSE_ELEMENT_HPP

#include <string>

#include "expresion.hpp"
#include "column.hpp"

namespace orm {

/**
 * \brief base class of where expresions,
 * this class exists becouse teorically 1=1 or :param = :apram are valids expresions that not fit in derived class
 * and others combinations that should not be used really, but i want support at some point
 * */
class ClauseElement : public orm::Expresion {
	public:
	std::string bindparam; // Name of the parameter
	/// todo
	virtual operator const std::string() { return (std::string)""; };
};

}

#endif


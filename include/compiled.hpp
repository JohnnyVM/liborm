#ifndef LIBORM_COMPILED_HPP
#define LIBORM_COMPILED_HPP

#include <string>
#include <unordered_map>

#include "engine.hpp"

namespace orm {

class Expresion;

/**
 * \brief base class of where expresions,
 * this class exists becouse teorically 1=1 or :param = :apram are valids expresions that not fit in derived class
 * and others combinations that should not be used really, but i want support at some point
 * */
class Compiled {
	public:
	std::string dialect;
	std::unordered_map<std::string, struct c_type*>params;
	orm::Expresion* expresion;
	/// todo
	operator const std::string() { return (std::string)""; };
};

}

#endif


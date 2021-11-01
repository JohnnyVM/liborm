#ifndef LIBORM_DIALECT_HPP
#define LIBORM_DIALECT_HPP

#include <string>

/** Base class dialect implementing ANSI SQL */
class Dialect {
	std::string name = "ANSI";
};

#endif


#ifndef LIBORM_OP_HPP
#define LIBORM_OP_HPP

#include <string>

namespace orm {

/** Necesary in the future for now is simply a mirrored class */
class Op {
	const std::string value;

	Op(const std::string arg_value) : value(arg_value) {}
};

};

#endif


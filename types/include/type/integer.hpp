#ifndef LIBORM_MAPPER_COLUMN_INTEGER_HPP
#define LIBORM_MAPPER_COLUMN_INTEGER_HPP

#include <string>
#include <cstdint>

#include "type/engine.h"

namespace orm::type {

class Integer : public TypeEngine {
	public:
	Integer() : TypeEngine("integer", sizeof(intmax_t)) {}
};

}

#endif

#ifndef LIBORM_TYPE_DATETIME_HPP
#define LIBORM_TYPE_DATETIME_HPP

#include <chrono>

#include "type/engine.h"

namespace orm::type {

class DateTime : public virtual TypeEngine {
	public:
	DateTime() : TypeEngine("datetime", 0) {} // TODO
};

}

#endif
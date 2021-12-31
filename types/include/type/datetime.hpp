#ifndef LIBORM_TYPE_DATETIME_HPP
#define LIBORM_TYPE_DATETIME_HPP

#include <chrono>

#include "type/engine.hpp"

namespace orm::type {

class Datetime : public orm::TypeEngine {
	public:
	Datetime() : orm::TypeEngine("datetime", 0) {} // TODO
};

}

#endif
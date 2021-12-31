#ifndef LIBORM_TYPE_DATE_HPP
#define LIBORM_TYPE_DATE_HPP

#include <ctime>

#include "type/engine.hpp"

namespace orm::type {

class Date : public orm::TypeEngine {
	public:
	Date() : orm::TypeEngine("date", sizeof(struct tm)) {}
};

}

#endif
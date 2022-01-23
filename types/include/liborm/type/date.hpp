#ifndef LIBORM_TYPE_DATE_HPP
#define LIBORM_TYPE_DATE_HPP

#include <ctime>

#include "liborm/type/engine.h"

namespace orm::type {

class Date : public virtual TypeEngine {
	public:
	Date() : TypeEngine("date", typeid(*this), sizeof(struct tm)) {}

	
};

}

#endif
#ifndef LIBORM_QUERY_HPP
#define LIBORM_QUERY_HPP

#include <string>
#include <memory>

#include "expresion.hpp"
#include "selectable.hpp"

namespace orm {

class Query : public orm::Expresion {
	public:
	virtual operator const std::string() = 0;
	Selectable *object;

	Query() {}
	Query(Selectable* arg_selectable) : object(arg_selectable) {}

	virtual Query& operator()(Selectable* selectable);
};

}

#endif


#ifndef LIBORM_DELETE_HPP
#define LIBORM_DELETE_HPP

#include <string>
#include <memory>

#include "selectable.hpp"
#include "query.hpp"

namespace orm {

class Delete : public orm::Query {
	public:
	explicit operator const std::string() override;
	Selectable* object;

	Delete(Selectable* arg_selectable) : object(arg_selectable) {}
};

}

#endif


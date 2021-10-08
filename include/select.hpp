#ifndef LIBORM_SELECT_HPP
#define LIBORM_SELECT_HPP

#include <string>
#include <memory>

#include "selectable.hpp"
#include "query.hpp"

namespace orm {

class Select : public orm::Query {
	public:
	explicit operator const std::string() override;

	Select(Selectable* arg_selectable) : orm::Query(arg_selectable) {}
};

}

#endif


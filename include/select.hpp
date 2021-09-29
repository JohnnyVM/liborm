#ifndef LIBORM_SELECT_HPP
#define LIBORM_SELECT_HPP

#include <string>
#include <memory>

#include "selectable.hpp"
#include "table.hpp"
#include "expresion.hpp"

namespace orm {

class Select : public orm::Expresion {
	public:
	explicit operator const std::string() override;
	std::shared_ptr<Selectable> object;

	Select(Selectable* arg_selectable) : object(arg_selectable) {}
};

}

#endif


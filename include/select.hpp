#ifndef LIBORM_SELECT_HPP
#define LIBORM_SELECT_HPP

#include <string>
#include <memory>

#include "schema_element.hpp"
#include "table.hpp"
#include "expresion.hpp"

namespace orm {

class Select : public orm::Expresion {
	public:
	Select(orm::Selectable* el) : orm::Expresion(el){}

	explicit operator const std::string() override;
};

}

#endif


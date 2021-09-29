#ifndef LIBORM_DELETE_HPP
#define LIBORM_DELETE_HPP

#include <string>
#include <memory>

#include "selectable.hpp"
#include "expresion.hpp"

namespace orm {

class Delete : public orm::Expresion {
	public:
	explicit operator const std::string() override;
	std::shared_ptr<Selectable> object;

	Delete(Selectable* arg_selectable) : object(arg_selectable) {}
};

}

#endif


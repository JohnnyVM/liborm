#ifndef LIBORM_TYPES_FACTORY_HPP
#define LIBORM_TYPES_FACTORY_HPP

#include <typeinfo>
#include <cassert>
#include <stdexcept>
#include <string>

#include "type/string.hpp"
#include "type/numeric.hpp"
#include "type/integer.hpp"
#include "type/engine.h"

namespace orm {

class TypeFactory {
	public:
	TypeFactory() {}
	virtual ~TypeFactory() {}
	virtual TypeEngine* String() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual TypeEngine* Integer() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual TypeEngine* Numeric() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual TypeEngine* Date() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual TypeEngine* DateTime() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual TypeEngine* Boolean() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual TypeEngine* Float() { throw std::logic_error((std::string)"Type " + __func__ + " not supported by driver"); return nullptr; }
	virtual const std::type_info& coerced_type() = 0;
	TypeEngine* factory(const std::type_info& type) {
		if(type == typeid(orm::type::String)) { // UGH...
			return String();
		}
		if(type == typeid(orm::type::Integer)) {
			return Integer();
		}
		if(type == typeid(orm::type::Numeric)) {
			return Numeric();
		}
		throw std::logic_error((std::string)"Type " + type.name() + " not supported");
		return nullptr;
	}
	TypeEngine* factory() {
		return factory(coerced_type());
	}
};

}

#endif

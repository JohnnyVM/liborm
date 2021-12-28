#ifndef LIBORM_TYPES_FACTORY_HPP
#define LIBORM_TYPES_FACTORY_HPP

#include <typeinfo>
#include <cassert>
#include <stdexcept>
#include <string>

#include "type/string.hpp"
#include "type/numeric.hpp"
#include "type/integer.hpp"
#include "type/engine.hpp"

namespace orm {

/**
 * \brief Factory virtual class for TypeEngine 
 * Each implementation should transform the DBAPI base data in TypeEngine or die if not posible
 * \todo this should be asociated to a dialect / driver and shared betwen engine cursor and connection
 */
class TypeFactory {
	public:
	virtual ~TypeFactory() {};
	virtual TypeEngine* String() { assert(!"Type not supported by driver"); return nullptr; }
	virtual TypeEngine* Integer() { assert(!"Type not supported by driver"); return nullptr; }
	virtual TypeEngine* Numeric() { assert(!"Type not supported by driver"); return nullptr; }
	virtual TypeEngine* Date() { assert(!"Type not supported by driver"); return nullptr; }
	virtual TypeEngine* DateTime() { assert(!"Type not supported by driver"); return nullptr; }
	virtual TypeEngine* Boolean() { assert(!"Type not supported by driver"); return nullptr; }
	virtual TypeEngine* Float() { assert(!"Type not supported by driver"); return nullptr; }
	virtual const std::type_info& coerced_type() = 0; /**< return the expected type */
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
		assert(!"Type not supported");
		return nullptr;
	}
	TypeEngine* factory() {
		return factory(coerced_type());
	}
};

}

#endif

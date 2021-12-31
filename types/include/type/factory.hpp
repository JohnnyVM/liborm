#ifndef LIBORM_TYPES_FACTORY_HPP
#define LIBORM_TYPES_FACTORY_HPP

#include <typeinfo>
#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>

#include "type/types.hpp"

namespace orm {

/**
 * \brief Factory virtual class for TypeEngine 
 * Each implementation should transform the DBAPI base data in TypeEngine or die if not posible
 * \todo this should be asociated to a dialect / driver and shared betwen engine cursor and connection
 */
class TypeFactory {
	public:
	virtual ~TypeFactory() {};
	virtual std::shared_ptr<orm::TypeEngine> String() { assert(!"Type not supported by driver"); return nullptr; }
	virtual std::shared_ptr<orm::TypeEngine> Integer() { assert(!"Type not supported by driver"); return nullptr; }
	virtual std::shared_ptr<orm::TypeEngine> Numeric() { assert(!"Type not supported by driver"); return nullptr; }
	virtual std::shared_ptr<orm::TypeEngine> Date() { assert(!"Type not supported by driver"); return nullptr; }
	virtual std::shared_ptr<orm::TypeEngine> DateTime() { assert(!"Type not supported by driver"); return nullptr; }
	virtual std::shared_ptr<orm::TypeEngine> Boolean() { assert(!"Type not supported by driver"); return nullptr; }
	virtual std::shared_ptr<orm::TypeEngine> Float() { assert(!"Type not supported by driver"); return nullptr; }
	virtual const std::type_info& coerced_type() = 0; /**< return the expected type */
	std::shared_ptr<orm::TypeEngine> factory(const std::type_info& type) {
		if(type == typeid(orm::type::String)) { // UGH...
			return String();
		}
		if(type == typeid(orm::type::Integer)) {
			return Integer();
		}
		if(type == typeid(orm::type::Numeric)) {
			return Numeric();
		}
		if(type == typeid(orm::type::Date)) {
			return Numeric();
		}
		if(type == typeid(orm::type::Datetime)) {
			return Numeric();
		}
		if(type == typeid(orm::type::Boolean)) {
			return Numeric();
		}
		if(type == typeid(orm::type::Float)) {
			return Numeric();
		}
		assert(!"Type not supported");
		return nullptr;
	}
	std::shared_ptr<orm::TypeEngine> factory() {
		return factory(coerced_type());
	}
};

}

#endif

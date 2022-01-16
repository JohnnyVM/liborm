#ifndef LIBORM_TYPES_FACTORY_HPP
#define LIBORM_TYPES_FACTORY_HPP

#include <typeinfo>
#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>
#include <any>

#include "liborm/type/types.hpp"

namespace orm {

/**
 * \brief Factory virtual class for TypeEngine 
 * Each implementation should transform the DBAPI base data in TypeEngine or die if not posible
 * \todo this should be asociated to a dialect / driver and shared betwen engine cursor and connection
 * \todo ideally i need find some way to define here the bind_processor step
 */
class TypeFactory {
	public:
	virtual ~TypeFactory() {};
	[[nodiscard]] virtual std::unique_ptr<orm::type::String> String() const = 0;
	[[nodiscard]] virtual std::unique_ptr<orm::type::Integer> Integer() const { assert(!"Type not supported by driver"); return nullptr; }
	[[nodiscard]] virtual std::unique_ptr<orm::type::Numeric> Numeric() const = 0;
	[[nodiscard]] virtual std::unique_ptr<orm::type::Date> Date() const { assert(!"Type not supported by driver"); return nullptr; }
	[[nodiscard]] virtual std::unique_ptr<orm::type::Datetime> Datetime() const = 0;
	[[nodiscard]] virtual std::unique_ptr<orm::type::Boolean> Boolean() const { assert(!"Type not supported by driver"); return nullptr; }
	[[nodiscard]] virtual std::unique_ptr<orm::type::Float> Float() const { assert(!"Type not supported by driver"); return nullptr; }
	[[nodiscard]] virtual const std::type_info& coerced_type() const noexcept = 0; /**< return the expected type */
	std::unique_ptr<TypeEngine> factory(const std::type_info& type) const;
	inline std::unique_ptr<TypeEngine> factory() const  {
		return factory(coerced_type());
	}
};

}

#endif

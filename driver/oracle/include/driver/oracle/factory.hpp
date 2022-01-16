#ifndef LIBORM_DRIVER_ORACLE_TYPES_FACTORY_H
#define LIBORM_DRIVER_ORACLE_TYPES_FACTORY_H

#include <typeinfo>
#include <memory>

#include "oracle_types.h"
#include "liborm/type/string.hpp"
#include "liborm/type/integer.hpp"
#include "liborm/type/numeric.hpp"
#include "liborm/type/factory.hpp"

namespace driver::oracle {

class TypeFactory final : virtual public orm::TypeFactory {
	public:
	TypeFactory(struct ora_database_type *arg_data) : data(private_copy_data(arg_data)) {}
	const std::type_info& coerced_type() const noexcept override;
	static const std::type_info& coerced_type(enum sql_code) noexcept;
	std::unique_ptr<orm::type::Numeric> Numeric() const override;
	std::unique_ptr<orm::type::String> String() const override;
	std::unique_ptr<orm::type::Datetime> Datetime() const override;
	~TypeFactory() = default;
	private:
	std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> data;
	inline static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> private_copy_data(struct ora_database_type* arg) noexcept {
		std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> ptr(ora_database_type_clone(arg), &free_ora_database_type);
		return ptr;
	}
};

std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param(std::shared_ptr<TypeEngine const> _val);

}

#endif

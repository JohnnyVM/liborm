#ifndef LIBORM_DRIVER_ORACLE_TYPES_FACTORY_H
#define LIBORM_DRIVER_ORACLE_TYPES_FACTORY_H

#ifndef __cplusplus

typedef struct OracleTypeFactory OracleTypeFactory;

#else

#include <typeinfo>
#include <memory>

#include "oracle_types.h"
#include "type/string.hpp"
#include "type/integer.hpp"
#include "type/numeric.hpp"
#include "type/factory.hpp"

namespace driver::oracle {

class TypeFactory : virtual public orm::TypeFactory {
	public:
	TypeFactory(struct ora_database_type *arg_data) : data(private_copy_data(arg_data)) {}
	const std::type_info& coerced_type() override;
	std::shared_ptr<orm::TypeEngine> Numeric() override;
	~TypeFactory() = default;
	private:
	std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> data;
	static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> private_copy_data(struct ora_database_type* arg) noexcept {
		std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> ptr(ora_database_type_clone(arg), &free_ora_database_type);
		return ptr;
	}
};

}

#endif

#endif

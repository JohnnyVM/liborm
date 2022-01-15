#include <memory>
#include <stdexcept>

#include "type/types.hpp"
#include "driver/oracle/factory.hpp"
#include "oracle_types.h"
#include "inner_driver_oracle.h"

const std::type_info& driver::oracle::TypeFactory::coerced_type(enum sql_code code) {
	switch(code) {
		case ORA_ORACLE_NUMBER: /**< char[n] (n<=22) */
		case ORA_NUMBER:
			return typeid(orm::type::Numeric);
		case ORA_CHARACTER:
		case ORA_CHARACTER_VARYING:
		case ORA_STRING: /**< char[n+1] */
		case ORA_ORACLE_VARCHAR: /**< char[n+2] */
		case ORA_VARCHAR2: /**< char[n] */
			return typeid(orm::type::String);
		case ORA_DATE:
			return typeid(orm::type::Datetime);
		case ORA_DECIMAL:
		case ORA_DOUBLE_PRECISION:
		case ORA_FLOAT:
		case ORA_INTEGER:
		case ORA_REAL:
		case ORA_SMALLINT:
		case ORA_ORACLE_FLOAT: /**< float */
		case ORA_BINARY_FLOAT:
		case ORA_BINARY_DOUBLE:
		default:
			assert(!"Not implemented");
			return typeid(nullptr);
	}
}

const std::type_info& driver::oracle::TypeFactory::coerced_type() const {
	return driver::oracle::TypeFactory::coerced_type(data.get()->type);
}

std::unique_ptr<orm::type::Numeric> driver::oracle::TypeFactory::Numeric() const {
	assert(data.get()->precision > 0 && data.get()->scale >= 0);
	std::unique_ptr<orm::type::Numeric> out = std::make_unique<orm::type::Numeric>((unsigned)data.get()->precision, (unsigned)data.get()->scale);
	if(data.get()->indicator == -1) {
		out->is_null = true;
	} else {
		*out.get() = number_to_Decimal128(data.get()->data, data.get()->returned_length);
	}
	return out;
}

std::unique_ptr<orm::type::String> driver::oracle::TypeFactory::String() const {
	std::unique_ptr<orm::type::String> out = std::make_unique<orm::type::String>(data.get()->length);
	if(data.get()->indicator == -1) {
		out->is_null = true;
	} else {
		*out.get() = data.get()->data;
	}
	return out;
}

std::unique_ptr<orm::type::Datetime> driver::oracle::TypeFactory::Datetime() const {
	std::unique_ptr<orm::type::Datetime> out = std::make_unique<orm::type::Datetime>();
	if(data.get()->indicator == -1) {
		out->is_null = true;
	} else {
		assert(!"Not implemented");
	}
	return out;
}

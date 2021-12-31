#include <memory>
#include <stdexcept>

#include "type/types.hpp"
#include "driver/oracle/factory.hpp"
#include "oracle_types.h"
#include "inner_driver_oracle.h"

const std::type_info& driver::oracle::TypeFactory::coerced_type() const {
	switch(data.get()->type) {
		case ORA_NUMBER:
			return typeid(orm::type::Numeric);
		case ORA_CHARACTER:
		case ORA_CHARACTER_VARYING:
		case ORA_DATE:
		case ORA_DECIMAL:
		case ORA_DOUBLE_PRECISION:
		case ORA_FLOAT:
		case ORA_INTEGER:
		case ORA_REAL:
		case ORA_SMALLINT:
		case ORA_VARCHAR2: /**< char[n] */
		case ORA_ORACLE_NUMBER: /**< char[n] (n<=22) */
		case ORA_ORACLE_FLOAT: /**< float */
		case ORA_STRING: /**< char[n+1] */
		case ORA_ORACLE_VARCHAR: /**< char[n+2] */
		case ORA_BINARY_FLOAT:
		case ORA_BINARY_DOUBLE:
		default:
			assert(!"Not implemented");
			return typeid(nullptr);
	}
}

std::unique_ptr<orm::type::Numeric> driver::oracle::TypeFactory::Numeric() const {
	return std::make_unique<orm::type::Numeric>(data.get()->precision, data.get()->scale, number_to_Decimal128(data.get()->data, data.get()->returned_length));
}
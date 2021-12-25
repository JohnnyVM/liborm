#include <memory>
#include <stdexcept>

#include "factory.h"
#include "oracle_types.h"
#include "inner_driver_oracle.h"

driver::oracle::TypeFactory::TypeFactory (
		enum sql_code arg_type,
		int arg_length,
		short arg_returned_length,
		int arg_octet_length,
		short arg_returned_octet_length,
		int arg_precision,
		int arg_scale,
		int arg_nullable,
		short arg_indicator,
		char* arg_name,
		char* arg_character_set_name,
		unsigned char* arg_data)
:
		type(arg_type),
		length(arg_length),
		returned_length(arg_returned_length),
		octet_length(arg_octet_length),
		returned_octet_length(arg_returned_octet_length),
		precision(arg_precision),
		scale(arg_scale),
		nullable(arg_nullable),
		indicator(arg_indicator),
		name(arg_name),
		character_set_name(arg_character_set_name),
		data(arg_data, free_ptrm) {}

const std::type_info& driver::oracle::TypeFactory::coerced_type() {
	switch(type) {
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
			assert(0);
			throw std::logic_error("Not implemented");
			return typeid(nullptr);
	}
}

orm::type::Numeric* driver::oracle::TypeFactory::Numeric() {
			return new orm::type::Numeric(precision, scale, number_to_Decimal128(data.get(), returned_length));
}

TypeEngine* oracleTypeFactory(
	enum sql_code type,
	int length,
	short returned_length,
	int octet_length,
	short returned_octet_length,
	int precision,
	int scale,
	int nullable,
	short indicator,
	char* name,
	char* character_set_name,
	unsigned char* data)
{
	driver::oracle::TypeFactory f(
			type,
			length,
			returned_length,
			octet_length,
			returned_octet_length,
			precision,
			scale,
			nullable,
			indicator,
			name,
			character_set_name,
			data);
	return f.factory();
}

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
	TypeFactory(
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
		char* haracter_set_name,
		unsigned char* data);
	const std::type_info& coerced_type() override;
	orm::type::Numeric* Numeric() override;
	~TypeFactory() {}
	private:
		enum sql_code type;
		int length;
		short returned_length;
		int octet_length;
		short returned_octet_length;
		int precision;
		int scale;
		int nullable;
		short indicator;
		const std::string name;
		const std::string character_set_name;
		std::unique_ptr<unsigned char, void(*)(void*)> data;
	static void free_ptrm(void* p) { std::free(p); }
};

}

#endif

#ifdef __cplusplus
extern "C" {
#endif

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
	unsigned char* data);

#ifdef __cplusplus
}
#endif

#endif

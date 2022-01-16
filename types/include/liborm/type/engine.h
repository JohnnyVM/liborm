#ifndef LIBORM_TYPE_ENGINE_H
#define LIBORM_TYPE_ENGINE_H

#include <stddef.h>

#ifndef __cplusplus

typedef struct TypeEngine TypeEngine;
#ifndef ORA_PROC
typedef _Decimal128 decimal128;
#else
typedef long long decimal128;
#endif

#else

#include <decimal/decimal>
using decimal128 = std::decimal::decimal128;
namespace orm::type {
	class Numeric;
	class Integer;
}

#include <cstdlib>
#include <string>
#include <stdexcept>
#include <memory>

class TypeEngine { // Keep that separate for class slicing
	public:
	const size_t length;
	const std::string name;
	virtual ~TypeEngine() {}
	TypeEngine(std::string arg_name, const std::type_info& arg_type, size_t arg_length)
	: length(arg_length), name(arg_name), type(arg_type), is_null(false) {}
	virtual explicit operator std::string() const = 0; /**< convenience method */
	inline std::string bind_expression() const { return std::string(":") + name; }

	inline friend std::string StringFrom(TypeEngine& arg) {
		return std::string(arg);
	}
	inline friend std::string to_string(const TypeEngine& _engine) {
    	return std::string(_engine);
  	}
	virtual std::unique_ptr<TypeEngine> clone() const = 0;

	const std::type_info& type;
	bool is_null; // null value
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

int column_as_char(TypeEngine* const, char**buf, size_t len);
int column_as_int(TypeEngine* const val);
long column_as_long(TypeEngine* const val);
float column_as_float(TypeEngine* const val);
double column_as_double(TypeEngine* const val);
long long column_as_long_long(TypeEngine* const val);
long double column_as_long_double(TypeEngine* const val);
decimal128 column_as_decimal128(TypeEngine* const val);

#ifdef __cplusplus
}
#endif

#endif
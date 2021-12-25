#ifndef LIBORM_MAPPER_COLUMN_BASE_HPP
#define LIBORM_MAPPER_COLUMN_BASE_HPP

#ifndef __cplusplus

typedef struct TypeEngine TypeEngine;

#else

#include <cstdlib>
#include <string>
#include <stdexcept>

class TypeEngine { // Keep that separate for class slicing
	public:
	const size_t length;
	const std::string name;
	virtual ~TypeEngine(){}
	TypeEngine(std::string arg_name, size_t arg_length) : length(arg_length), name(arg_name) {}
	std::string bind_expression() { return (std::string)":" + name; }
	/* \todo
	 * bind_processor() Return a conversion function for processing bind values.
	 */
	template<typename T>
	operator T() {
		std::logic_error((std::string)"Cast " + typeid(*this).name() + " -> " + typeid(T).name() + " not implemented");
	}
};

#endif

#endif

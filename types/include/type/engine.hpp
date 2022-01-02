#ifndef LIBORM_TYPE_ENGINE_HPP
#define LIBORM_TYPE_ENGINE_HPP

#include <cstdlib>
#include <string>
#include <stdexcept>

namespace orm {

class TypeEngine { // Keep that separate for class slicing
	public:
	const size_t length;
	const std::string name;
	virtual ~TypeEngine() {}
	TypeEngine(std::string arg_name, size_t arg_length) : length(arg_length), name(arg_name) {}
	inline std::string bind_expression() const { return (std::string)":" + name; }
	/* \todo
	 * bind_processor() Return a conversion function for processing bind values.
	 */
	virtual explicit operator std::string() const = 0; /**< convenience method */
	inline friend std::string to_string(const TypeEngine& _engine) {
    	return std::string(_engine);
  	}
};

}

#endif

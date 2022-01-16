#include <memory>

#include "type/string.hpp"

std::unique_ptr<TypeEngine> orm::String(size_t size) {
	return std::make_unique<orm::type::String>(size);
}

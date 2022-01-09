#include <memory>
#include <string>

#include "mapper/column.hpp"

std::unique_ptr<orm::Column> orm::column(const std::string& name, std::unique_ptr<TypeEngine>targ) {
	return std::make_unique<orm::Column>(name, targ->clone());
}

std::unique_ptr<orm::Column> orm::column(const std::string& name, std::unique_ptr<TypeEngine>targ, const struct non_primary_key_nullable& pknulla) {
	return std::make_unique<orm::Column>(name, targ->clone(), pknulla);
}

std::unique_ptr<TypeEngine> orm::Numeric(unsigned precision) {
	return std::make_unique<orm::type::Numeric>(precision, 0U);
}
std::unique_ptr<TypeEngine> orm::Numeric(unsigned precision, unsigned scale) {
	return std::make_unique<orm::type::Numeric>(precision, scale);
}

std::unique_ptr<TypeEngine> orm::String(size_t size) {
	return std::make_unique<orm::type::String>(size);
}

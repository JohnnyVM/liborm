#include <memory>
#include <stdexcept>
#include <cstring>
#include <limits>

#include "liborm/type/types.hpp"
#include "driver/oracle/factory.hpp"
#include "oracle_types.h"
#include "inner_driver_oracle.h"

const std::type_info& driver::oracle::TypeFactory::coerced_type(enum sql_code code) noexcept {
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

const std::type_info& driver::oracle::TypeFactory::coerced_type() const noexcept {
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
		*out.get() = ora_date_to_tm(data.get()->data);
	}
	return out;
}


static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param([[maybe_unused]]const orm::type::Null& _val) {
	struct ora_database_type val;
	val.type = ORA_INTEGER;
	val.indicator = -1;
	std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> ptr(ora_database_type_param_clone(&val), &free_ora_database_type);
    return ptr;
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param(const orm::type::String& _val) {
	struct ora_database_type val;
	val.type = ORA_CHARACTER_VARYING;
	if(_val.is_null) {
		return bind_param(orm::type::Null());
	}
	assert(std::string(_val).length() <= std::numeric_limits<int>::max());
	val.length = (int)std::string(_val).length();
	val.indicator = _val.is_null ? -1 : 0;
	val.data = (unsigned char*)malloc(val.length);
	memcpy(val.data, std::string(_val).c_str(), val.length);
	std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> ptr(ora_database_type_param_clone(&val), &free_ora_database_type);
	free(val.data);
	return ptr;
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param(const orm::type::Integer& _val) {
	struct ora_database_type val;
	val.type = ORA_INTEGER;
	if(_val.is_null) {
		return bind_param(orm::type::Null());
	}
	assert(_val.length <= std::numeric_limits<int>::max());
	val.length = (int)_val.length;
	val.indicator = _val.is_null ? -1 : 0;
	val.data = (unsigned char*)malloc(val.length);
	intmax_t in = (intmax_t)_val;
	memcpy(val.data, &in, val.length);
	std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> ptr(ora_database_type_param_clone(&val), &free_ora_database_type);
	free(val.data);
	return ptr;
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param([[maybe_unused]]const orm::type::Numeric& val) {
	assert(!"Type not supported");
	return {nullptr, nullptr};
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param([[maybe_unused]]const orm::type::Datetime& val) {
	assert(!"Type not supported");
	return {nullptr, nullptr};
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param([[maybe_unused]]const orm::type::Date& val) {
	assert(!"Type not supported");
	return {nullptr, nullptr};
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param([[maybe_unused]]const orm::type::Float& val) {
	assert(!"Type not supported");
	return {nullptr, nullptr};
}

static std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> bind_param([[maybe_unused]]const orm::type::Boolean& val) {
	assert(!"Type not supported");
	return {nullptr, nullptr};
}

std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> driver::oracle::bind_param(std::shared_ptr<TypeEngine const> _val) {
	const std::type_info& type = _val->type;
    if(type == typeid(orm::type::String)) { // UGH again...
		const orm::type::String& val = dynamic_cast<const orm::type::String&>(*_val.get());
        return bind_param(val);
    }
    if(type == typeid(orm::type::Integer)) {
		const orm::type::Integer& val = dynamic_cast<const orm::type::Integer&>(*_val.get());
        return bind_param(val);
    }
    if(type == typeid(orm::type::Numeric)) {
		const orm::type::Numeric& val = dynamic_cast<const orm::type::Numeric&>(*_val.get());
        return bind_param(val);
    }
    if(type == typeid(orm::type::Date)) {
		const orm::type::Date& val = dynamic_cast<const orm::type::Date&>(*_val.get());
        return bind_param(val);
    }
    if(type == typeid(orm::type::Datetime)) {
		const orm::type::Datetime& val = dynamic_cast<const orm::type::Datetime&>(*_val.get());
        return bind_param(val);
    }
    if(type == typeid(orm::type::Boolean)) {
		const orm::type::Boolean& val = dynamic_cast<const orm::type::Boolean&>(*_val.get());
        return bind_param(val);
    }
    if(type == typeid(orm::type::Float)) {
		const orm::type::Float& val = dynamic_cast<const orm::type::Float&>(*_val.get());
        return bind_param(val);
    }
    assert(!"Type not supported");
	throw std::runtime_error("Type not supported");
    return {nullptr, nullptr};
}
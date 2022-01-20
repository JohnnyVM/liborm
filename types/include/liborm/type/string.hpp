#ifndef LIBORM_COLUMN_VARCHAR_HPP
#define LIBORM_COLUMN_VARCHAR_HPP

#include <string>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <cassert>

#include "liborm/type/engine.h"

namespace orm::type {

// https://docs.sqlalchemy.org/en/14/core/type_basics.html
class String : public TypeEngine { // Keep that separate for class slicing
	public:
	String(size_t arg_length, unsigned char* value) : String(arg_length, std::string(reinterpret_cast< char const* >(value))) {}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
	String(size_t arg_length, const T& value) : String(arg_length, std::string(value)) {}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
	String( const T& value, size_t arg_length) : String(arg_length, std::string(value)) {}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
	String(const T& value) : String(std::string(value).length(), std::string(value)) {}
	String(size_t arg_length, const std::string& value) :
		TypeEngine(init_name(minimun_is_1(arg_length)), typeid(*this), minimun_is_1(arg_length)), _value(value)
		{ if(_value.length() > length) { assert(!"Input string truncated"); throw std::length_error("Input string truncated"); } }
	String(size_t arg_length) :
		TypeEngine(init_name(minimun_is_1(arg_length)), typeid(*this), minimun_is_1(arg_length)) {}

	std::unique_ptr<TypeEngine> clone() const { return std::make_unique<String>(length, _value); }

	inline explicit operator std::string() const {return _value;}
	inline friend std::string StringFrom(String& arg) {
		return is_null ? std::string() : arg._value;
	}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline String& operator=(const T& __rhs) {
		std::string tmp = std::string(__rhs);
		if(tmp.length() > length) {
			assert(!"Input string truncated");
			throw std::length_error("Input string truncated"); // warning
		}
		_value = tmp;
		return *this;
	}
	inline String& operator=(const unsigned char* const __restrict __rhs) {
		std::string tmp = std::string((char*)__rhs);
		if(tmp.length() > length) {
			assert(!"Input string truncated");
			throw std::length_error("Input string truncated"); // warning
		}
		_value = tmp;
		return *this;
	}

	inline friend std::string operator+(const String& __lhs, const String& __rhs) {
		return __lhs._value + __rhs._value;
	}
	
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline friend std::string operator+(const String& __lhs, const T& __rhs) {
		return __lhs._value + std::string(__rhs);
	}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline friend std::string operator+(const T& __lhs, const String& __rhs) {
		return std::string(__lhs) + __rhs._value;
	}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline friend bool operator==(const T& __lhs, const String& __rhs) {
		return std::string(__lhs) == __rhs._value;
	}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline friend bool operator==(const String& __lhs, const T& __rhs) {
		return __lhs._value == std::string(__rhs);
	}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline friend bool operator!=(const T& __lhs, const String& __rhs) {
		return std::string(__lhs) != __rhs._value;
	}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline friend bool operator!=(const String& __lhs, const T& __rhs) {
		return __lhs._value != std::string(__rhs);
	}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline String& operator+=(const T& rhs) {
		if(_value.length() + std::string(rhs).length() > length) {
			assert(!"Input string truncated");
			throw std::length_error("Input string truncated");
		}
		_value += std::string(rhs);
		return *this;
	}

	private:
	std::string _value;
	inline static std::string init_name(size_t length) {
		return "character varying(" + std::to_string(length) + ")";
	}
	inline static size_t minimun_is_1(size_t len) { return len >= 1 ? len : 1; }
};

}

namespace orm {

std::unique_ptr<TypeEngine> String(size_t);

template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
inline std::unique_ptr<TypeEngine> String(const T& val) {
	return std::make_unique<orm::type::String>(val);
}

template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
inline std::unique_ptr<TypeEngine> String(size_t size, const T& val) {
	return std::make_unique<orm::type::String>(size, val);
}

template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
inline std::unique_ptr<TypeEngine> String(const T& val, size_t size) {
	return std::make_unique<orm::type::String>(size, val);
}

}

#endif


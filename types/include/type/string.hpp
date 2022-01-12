#ifndef LIBORM_COLUMN_VARCHAR_HPP
#define LIBORM_COLUMN_VARCHAR_HPP

#include <string>
#include <stdexcept>
#include <type_traits>
#include <memory>

#include "type/engine.h"

namespace orm::type {

// https://docs.sqlalchemy.org/en/14/core/type_basics.html
class String : public TypeEngine { // Keep that separate for class slicing
	public:
	String(size_t arg_length, unsigned char* value) : String(arg_length, std::string(reinterpret_cast< char const* >(value))) {}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	String(size_t arg_length, T value) : String(arg_length, std::string(value)) {}
	String(size_t arg_length, const std::string& value) :
		TypeEngine(init_name(minimun_is_1(arg_length)), typeid(*this), minimun_is_1(arg_length)), _value(value)
		{ if(_value.length() > length) { throw std::length_error("Input string truncated"); } }
	String(size_t arg_length) :
		TypeEngine(init_name(minimun_is_1(arg_length)), typeid(*this), minimun_is_1(arg_length)) {}

	std::unique_ptr<TypeEngine> clone() const { return std::make_unique<String>(length, _value); }

	inline explicit operator std::string() const {return _value;}
	inline friend std::string StringFrom(String& arg) {
		return arg._value;
	}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	inline String& operator=(const T& __rhs) {
		_value = std::string(__rhs);
		return *this;
	}
	inline String& operator=(const unsigned char* const __restrict __rhs) {
		_value = std::string((char*)__rhs);
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
		if(_value.length() + std::string(rhs).length() > this->length) {
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

#endif


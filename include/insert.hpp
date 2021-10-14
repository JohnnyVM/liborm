#ifndef LIBORM_INSERT_HPP
#define LIBORM_INSERT_HPP

#include <string>
#include <memory>
#include <type_traits>
#include <utility>
#include <stdexcept>

#include "selectable.hpp"
#include "query.hpp"

namespace orm {

class Insert : public orm::Query {
	private:
	// in C++20 move that to template template parameter and designated initializer for
	// easy values initializers
	// Right now is not very handy
	template<typename T>
	struct insert_definition_char {
	    std::string column;
	    T value;
	};

	public:
	explicit operator const std::string() override;
	Insert& operator() (Selectable* selectable) override;

	/* */
	std::vector<std::pair<std::string,std::string> >_values;

	Insert() : orm::Query() {}
	Insert(Selectable* arg_selectable) : orm::Query(arg_selectable) {}

	// This templates have to change in C++17(enable_if/is_aritmetic_v)
	template<
		typename V,
		typename = std::enable_if_t<std::is_arithmetic<V>::value>
	>
	Insert& values(std::string key, V value) {
		_values.push_back(std::pair<std::string,std::string>(key, std::to_string(value)));
		return *this;
	}
	template<
		typename V,
		typename = std::enable_if_t<!std::is_arithmetic<V>::value>
	>
	Insert& values(std::string key, V const& value) {
	_values.push_back(std::pair<std::string,std::string>(key, (std::string)"'" + std::string(value) + "'")); // add quote
	return *this;
	}
};

}

#endif


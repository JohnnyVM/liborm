#include <exception>
#include <string>

#include "insert.hpp"
#include "selectable.hpp"

orm::Insert& orm::Insert::operator() (orm::Selectable* selectable) {
	this->object = selectable;
	return *this;
}


orm::Insert::operator const std::string() {
	size_t i;
	std::string os = (std::string)"insert into " + object->name + " ";

	for(i=0; i < _values.size(); i++) {
		os += (std::string)(i ? "," : "") + _values[i].first;
	}

	os += (std::string)" values(";

	for(i=0; i < _values.size(); i++) {
		os += (std::string)(i ? "," : "") + _values[i].second;
	}

	os += (std::string)")";

	return os;
}


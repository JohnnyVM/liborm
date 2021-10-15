#include <exception>
#include <string>
#include <utility>
#include <vector>
#include <map>

#include "insert.hpp"
#include "selectable.hpp"
#include "column.hpp"

orm::Insert& orm::Insert::operator() (orm::Selectable* selectable) {
	this->object = selectable;
	return *this;
}

static std::string operator_params(orm::Insert& ins) {
	size_t i=0;
	std::string os = (std::string)"insert into " + ins.object->name + " ";

	std::map<std::string, std::string>::iterator itr;
	for(itr = ins.params.begin(); itr != ins.params.end(); itr++, i++) {
		os += (std::string)(i ? "," : "") + itr->first;
	}

	os += (std::string)" values(";

	i = 0;
	for(itr = ins.params.begin(); itr != ins.params.end(); itr++, i++) {
		os += (std::string)(i ? "," : "") + ":" + itr->first;
	}

	os += (std::string)")";

	return os;
};

static std::string operator_columns(orm::Insert& ins) {
	size_t i;
	std::string os = (std::string)"insert into " + ins.object->name + " ";

	for(i=0; i < ins.object->columns.size(); i++) {
		os += (std::string)(i ? "," : "") + ins.object->columns[i]->name;
	}

	os += (std::string)" values(";

	for(i=0; i < ins.object->columns.size(); i++) {
		os += (std::string)(i ? "," : "") + ":" + ins.object->columns[i]->name;
	}

	os += (std::string)")";

	return os;
};

orm::Insert::operator const std::string() {
	// if no params specified return list of columns
	if (params.size()) {
		return operator_params(*this);
	}

	return operator_columns(*this);
}


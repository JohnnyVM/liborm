#ifndef LIBORM_SELECT_HPP
#define LIBORM_SELECT_HPP

#include <string>
#include <memory>

#include "table.hpp"
#include "query.hpp"

namespace orm {

class Select : public orm::Query {
	public:
	explicit operator const std::string() override;

	Select(Table* arg_table) : orm::Query(arg_table) {}
};

}

#endif


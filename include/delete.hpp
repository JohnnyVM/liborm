#ifndef LIBORM_DELETE_HPP
#define LIBORM_DELETE_HPP

#include <string>
#include <memory>

#include "table.hpp"
#include "query.hpp"

namespace orm {

class Delete : public orm::Query {
	public:
	explicit operator const std::string() override;
	Table* object;

	Delete(Table* arg_table) : object(arg_table) {}
};

}

#endif


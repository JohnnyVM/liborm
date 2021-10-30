#ifndef LIBORM_QUERY_HPP
#define LIBORM_QUERY_HPP

#include <string>
#include <vector>

#include "clause_list.hpp"
#include "expresion.hpp"
#include "table.hpp"

namespace orm {

/* intermediate class for no redefine operator() for insert select and delete create */
class Query : public orm::Expresion {
	public:
	virtual operator const std::string() = 0;
	Table *object;

	Query() {}
	Query(Table* arg_table) : object(arg_table) {}

	std::vector<orm::ClauseList> clauses;

	virtual Query& operator()(Table* table);
	virtual Query& where(orm::ClauseList clause);// i cannot found how trick this
	/* methods */
};

}

#endif


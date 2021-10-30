#include "query.hpp"
#include "clause_list.hpp"
#include "table.hpp"

/**boiler plate code to ciopy apste by constructor */
orm::Query& orm::Query::operator()(Table* table) {
	this->object = table;
	return *this;
}


orm::Query& orm::Query::where(orm::ClauseList clause) {
	clauses.push_back(clause);
	return *this;
}


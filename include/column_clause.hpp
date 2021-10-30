#ifndef LIBORM_COLUMN_CLAUSE_HPP
#define LIBORM_COLUMN_CLAUSE_HPP

#include <string>

#include "column.hpp"
#include "clause_element.hpp"

namespace orm {

/**
 * \brief base class of where expresions for columns,
 * */
class ColumnClause : public orm::ClauseElement {
	public:
	orm::Column* column;
	std::string operation; // <,>,!=,like, etc
	/// todo
	virtual operator const std::string() { return (std::string)""; };
};

}

#endif


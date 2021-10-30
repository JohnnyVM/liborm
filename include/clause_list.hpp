#ifndef LIBORM_CLAUSE_LIST_HPP
#define LIBORM_CLAUSE_LIST_HPP

#include <string>
#include <vector>

#include "clause_element.hpp"

namespace orm {

/**
 * \brief base class as group of ClauseElements
 */
class ClauseList {
	public:
	std::vector<orm::ClauseElement*>clauses;

	private:
	bool and_ = true; //the list is joined with and if not the list is joined with or
};

}

#endif


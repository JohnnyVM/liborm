#ifndef LIBORM_CLAUSE_LIST_HPP
#define LIBORM_CLAUSE_LIST_HPP

#include <string>
#include <memory>

#include "expresion.hpp"
#include "expresion.hpp"

namespace orm {

class ClauseList : public orm::Expresion {
	public:
	virtual operator const std::string() = 0;

	private:
	bool _union = true; //the list is joined with and if not the list is joined with or
};

}

#endif


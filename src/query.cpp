#include "query.hpp"
#include "selectable.hpp"

orm::Query& orm::Query::operator()(Selectable* selectable) {
	this->object = selectable;
	return *this;
}

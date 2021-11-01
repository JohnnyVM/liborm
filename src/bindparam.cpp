#include "bindparam.hpp"

orm::BindParam orm::bindparam(std::string name) {
	return BindParam(name);
}

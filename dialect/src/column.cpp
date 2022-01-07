#include <memory>
#include <string>

#include "mapper/column.hpp"

std::shared_ptr<orm::Column> orm::column(column_params p) {
	return std::make_shared<orm::Column>(p);
}


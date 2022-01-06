#include <memory>
#include <string>

#include "mapper/column.hpp"

std::unique_ptr<orm::Column> orm::column(column_params p) {
	return std::make_unique<orm::Column>(p);
}


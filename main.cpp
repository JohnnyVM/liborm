#include "column.hpp"

int main () {
	orm::Column col({
        .name = "col",
        .default_value = [](){return std::variant<uintmax_t, std::string, long double>("name");},
        .primary_key = false,
        .nullable = false
    });
	return 0;
}

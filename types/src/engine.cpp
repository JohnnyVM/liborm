#include <cstdio>

#include <string>
#include <decimal/decimal>
using decimal128 = std::decimal::decimal128;

#include "liborm/type/engine.h"
#include "liborm/type/numeric.hpp"

extern "C" {

int column_as_char(TypeEngine* const val, char**buf, size_t len) {
    std::string src = std::string(*val);

    return snprintf(*buf, len, "%s", src.c_str());
}

/* only numeric types meet that */
#define DECLARE_NUMERIC_CAST(TYPE) \
TYPE column_as_##TYPE(TypeEngine* const val) {orm::type::Numeric& n = dynamic_cast<orm::type::Numeric&>(*val); return (TYPE)n;}
DECLARE_NUMERIC_CAST(int)
DECLARE_NUMERIC_CAST(long)
DECLARE_NUMERIC_CAST(float)
DECLARE_NUMERIC_CAST(double)
long long column_as_long_long(TypeEngine* const val) {orm::type::Numeric& n = dynamic_cast<orm::type::Numeric&>(*val); return (long long)n;}
long double column_as_long_double(TypeEngine* const val) {orm::type::Numeric& n = dynamic_cast<orm::type::Numeric&>(*val); return (long double)n;}
decimal128 column_as_decimal128(TypeEngine* const val) {
    orm::type::Numeric& n = dynamic_cast<orm::type::Numeric&>(*val);
    return (decimal128)n;
}
#undef DECLARE_NUMERIC_CAST

}

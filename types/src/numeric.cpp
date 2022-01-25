#include <string>
#include <iomanip>
#include <sstream>
#include <decimal/decimal>

#include "liborm/type/numeric.hpp"
#include <cfloat>

orm::type::Numeric::operator std::string() const {
    std::stringstream stream;
    if(is_null) {
        return std::string();
    }
    assert(precision <= LDBL_DIG); // fail if the value precision is bigger than the expected output
    long double out = (long double)*this;

    /**
     * \warning set precision round the values, see tests typeengine, but the comparaision trunc
     */
    stream << std::fixed << std::setprecision(scale) << out;

    return stream.str();
}

std::unique_ptr<TypeEngine> orm::Numeric(unsigned precision) {
	return std::make_unique<orm::type::Numeric>(precision, 0U);
}
std::unique_ptr<TypeEngine> orm::Numeric(unsigned precision, unsigned scale) {
	return std::make_unique<orm::type::Numeric>(precision, scale);
}
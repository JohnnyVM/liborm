#include <string>
#include <iomanip>
#include <sstream>
#include <decimal/decimal>

#include "type/numeric.hpp"
#include <cfloat>


orm::type::Numeric::operator std::string() const {
    std::stringstream stream;

    assert(precision <= LDBL_DIG); // fail if the value precision is bigger than the expected output
    long double out = (long double)*this;

    /**
     * \warning set precision round the values, see tests typeengine, but the comparaision trunc
     */
    stream << std::fixed << std::setprecision(scale) << out;

    return stream.str();
}
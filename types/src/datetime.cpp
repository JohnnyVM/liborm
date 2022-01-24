#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cassert>
#include <mutex>
#include <string>
#include <atomic>

#include "liborm/type/datetime.hpp"

orm::type::Datetime orm::type::Datetime::now() {
    struct timespec nts;
    int err = clock_gettime(CLOCK_REALTIME, &nts);
    assert(err == 0);
    if(err != 0) { throw std::system_error(err, std::generic_category()); }
    return Datetime(nts);
}

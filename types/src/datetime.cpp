#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cassert>
#include <mutex>
#include <string>
#include <atomic>

#include "type/datetime.hpp"

orm::type::Datetime orm::type::Datetime::now() {
    struct timespec nts;
    int err = clock_gettime(CLOCK_REALTIME, &nts);
    assert(err == 0);
    if(err != 0) { throw std::system_error(err, std::generic_category()); }
    return Datetime(nts);
}

orm::type::Datetime::operator std::string() const {
    std::scoped_lock lock(orm::type::Datetime::lock_timer);
    setlocale(LC_TIME, ""); // danger, this can affect other parts of the program
    
    struct tm tm, *check;
    errno = 0;
    check = gmtime_r(&ts.tv_sec, &tm);
    if(check == NULL) { assert(!"gmtime_r error"); throw std::system_error(errno, std::generic_category()); }
    char out[100]; // i suppose is enought
    int icheck = strftime(out, sizeof out, nl_langinfo(D_T_FMT), &tm);
    assert(icheck < (int)sizeof out);

    return std::string(out);
}

std::string orm::type::Datetime::tostring() const {
    return std::string(*this);
}
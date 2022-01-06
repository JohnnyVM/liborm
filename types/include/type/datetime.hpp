#ifndef LIBORM_TYPE_DATETIME_HPP
#define LIBORM_TYPE_DATETIME_HPP

#include <system_error>
#include <string>
#include <langinfo.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <errno.h>
#include <cassert>
#include <mutex>

#include "type/engine.h"

static std::mutex lock_tostring;

namespace orm::type {

/**
 * \brief datetime format, the standart support until seconds but all implementation expand the precision
 * in some way...
 * 
 * The internal time respresentation is time since epoch, the input date is time locale and the output date too
 */
class Datetime : public virtual TypeEngine {
	public:
	~Datetime() = default;
	Datetime() noexcept : TypeEngine("datetime", sizeof(struct timespec)) {}
	Datetime(struct timespec arg) noexcept : TypeEngine("datetime", sizeof(struct timespec)), ts(arg) {}
	template<typename T,
		std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	Datetime(T arr) : TypeEngine("datetime", sizeof(struct timespec)) {
		if(std::string(arr) == "now" or std::string(arr) == "NOW") { // todo unicode
			int err = clock_gettime(CLOCK_REALTIME, &ts) // time from epoch
			assert(err == 0);
			if(err != 0) { throw std::system_error(err, std::generic_category()); }
			return;
		}
		// guess type
	}

	/**
	 * \brief return the time since epoch like string represented in locale format
	 * 
	 * debatable behaviour, but some default is necesary
	 * \return std::string 
	 */
	explicit operator std::string() const;

	/*transform ts in the specified format */
	std::string tostring() const;
	template<typename T,
		std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	std::string tostring(T val) const {
	    std::scoped_lock lock(Datetime::lock_timer);
		
		struct tm tm, *check;
		errno = 0;
		check = gmtime_r(&ts.tv_sec, &tm);
		if(check == NULL) { assert(!"gmtime_r error"); throw std::system_error(errno, std::generic_category()); }
		char out[100];
		int icheck = strftime(out, sizeof out, std::string(val).c_str(), &tm);
		assert(icheck < sizeof out);

		return std::string(out);
	}

	static Datetime now();

	private:
	struct timespec ts;
	inline static std::mutex lock_timer;
};

}

#endif
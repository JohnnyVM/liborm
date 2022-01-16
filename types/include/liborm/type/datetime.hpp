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
#include <memory>

#include "liborm/type/engine.h"

static std::mutex lock_tostring;

namespace orm::type {

/**
 * \brief datetime format, the standart support until seconds but all implementation expand the precision
 * in some way...
 *
 * The internal time respresentation is time since epoch, the input date is time locale and the default output date too
 */
class Datetime : public virtual TypeEngine {
	public:
	~Datetime() = default;
	Datetime() noexcept : TypeEngine("datetime", typeid(*this), sizeof(struct timespec)) {}
	Datetime(struct timespec arg) noexcept : TypeEngine("datetime", typeid(*this), sizeof(struct timespec)), ts(arg) {}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	Datetime(T arr) : TypeEngine("datetime", typeid(*this), sizeof(struct timespec)) {
		if(std::string(arr) == "now" or std::string(arr) == "NOW") { // todo unicode
			int err = clock_gettime(CLOCK_REALTIME, &ts) // time from epoch
			assert(err == 0);
			if(err != 0) { throw std::system_error(err, std::generic_category()); }
			return;
		}
	}

	std::unique_ptr<TypeEngine> clone() const override { return std::make_unique<Datetime>(ts); }

	inline bool operator!() const { return this->is_null ? true : false; }

#define _DATETIME_BINARY_OPERATOR(_Op) \
	inline friend bool operator _Op(const Datetime& _lhs, const Datetime& _rhs) { \
		return _lhs.is_null or _rhs.is_null ? false : (_lhs.ts.tv_sec _Op _rhs.ts.tv_sec) or ((_lhs.ts.tv_sec == _rhs.ts.tv_sec) and (_lhs.ts.tv_nsec _Op _rhs.ts.tv_nsec)); }
	_DATETIME_BINARY_OPERATOR(==)
	_DATETIME_BINARY_OPERATOR(!=)
	_DATETIME_BINARY_OPERATOR(>)
	_DATETIME_BINARY_OPERATOR(<)
	_DATETIME_BINARY_OPERATOR(>=)
	_DATETIME_BINARY_OPERATOR(<=)
#undef _DATETIME_BINARY_OPERATOR

#define _TIME_T_BINARY_OPERATOR(_Op) \
	inline friend bool operator _Op(const Datetime& _lhs, const time_t& _rhs) { \
		return _lhs.is_null ? false : (_lhs.ts.tv_sec _Op _rhs) or ((_lhs.ts.tv_sec == _rhs) and (_lhs.ts.tv_nsec _Op 0L)); } \
	inline friend bool operator _Op(const time_t& _lhs, const Datetime& _rhs) { \
		return _rhs.is_null ? false : (_lhs _Op _rhs.ts.tv_sec) or ((_lhs == _rhs.ts.tv_sec) and (0L _Op _rhs.ts.tv_nsec)); }
	_TIME_T_BINARY_OPERATOR(==)
	_TIME_T_BINARY_OPERATOR(!=)
	_TIME_T_BINARY_OPERATOR(>)
	_TIME_T_BINARY_OPERATOR(<)
	_TIME_T_BINARY_OPERATOR(>=)
	_TIME_T_BINARY_OPERATOR(<=)
#undef _TIME_T_BINARY_OPERATOR

	/**
	 * \brief return the time since epoch like string represented in locale format
	 *
	 * debatable behaviour, but some default is necesary
	 * \return std::string
	 */
	explicit operator std::string() const;
	inline explicit operator struct timespec() const { return ts; }
	inline explicit operator time_t() const { return ts.tv_sec; }

	/*transform ts in the specified format, todo check at compile time */
	std::string tostring() const;
	template<typename T,
		std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	std::string tostring(const T& val) const {
	    std::scoped_lock lock(Datetime::lock_timer);

		struct tm tm, *check;
		errno = 0;
		check = gmtime_r(&ts.tv_sec, &tm);
		if(check == NULL) { assert(!"gmtime_r error"); throw std::system_error(errno, std::generic_category()); }
		char out[100];
		int icheck = strftime(out, sizeof out, std::string(val).c_str(), &tm);
		assert(icheck != 0);

		return std::string(out);
	}

	static Datetime now();

	private:
	struct timespec ts;
	inline static std::mutex lock_timer;
};

}

#endif

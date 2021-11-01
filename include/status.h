#ifndef LIBORM_STATUS_H
#define LIBORM_STATUS_H

#ifdef __cplusplus
extern "C"
{
	namespace orm {
#endif

/** \brief list of error codes */
enum orm_status_code {
	NO_ERROR = 0,
	UNKNOW_ERROR = 1,
};

struct orm_status {
	enum orm_status_code error;
};

#ifdef __cplusplus
	}
}
#endif

#endif


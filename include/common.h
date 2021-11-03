#ifndef LIBORM_COMMON_H
#define LIBORM_COMMON_H

#ifdef __GNUC__
#define NO_DISCARD __attribute__((warn_unused_result))
#endif

#define INIT_DRIVER(DRIVER) __INIT_DRIVER__(DRIVER)
#define __INIT_DRIVER__(DRIVER) {\
.open = driver_##DRIVER##_open,\
.close = driver_##DRIVER##_close,\
.error_message = driver_##DRIVER##_error_message,\
}

#endif

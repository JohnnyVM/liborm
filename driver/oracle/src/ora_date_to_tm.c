#include <time.h>

struct tm ora_date_to_tm(unsigned char* arg) {
    struct tm out = {0};
    out.tm_isdst = -1; // the dst is unknow
    out.tm_year = ((int)arg[0] - 100) * 100 + ((int)arg[1] - 100) - 1900;
    out.tm_mon = (int)arg[2] - 1;
    out.tm_mday = (int)arg[3];
    out.tm_hour = (int)arg[4] - 1;
    out.tm_min = (int)arg[5] - 1;
    out.tm_sec = (int)arg[6] - 1;
    return out;
}
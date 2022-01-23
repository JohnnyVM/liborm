#include <time.h>

struct tm ora_date_to_tm(unsigned char* arg) {
    struct tm out = {0};
    out.tm_isdst = -1; // the dst is unknow
    if(arg) {}
    return out;
}
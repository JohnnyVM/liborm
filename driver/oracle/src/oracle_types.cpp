#include <cstdlib>
#include <cstring>

#include "oracle_types.h"

extern "C" {

void free_ora_database_type(struct ora_database_type *result) {
    if(result) {
        if(result->indicator != -1) {
            std::free(result->data);
        }
		std::free(result);
    }
}

struct ora_database_type* ora_database_type_clone(struct ora_database_type *src) {
	if(!src) {
        return NULL;
    }
	struct ora_database_type* dest = (struct ora_database_type*)malloc(sizeof *dest);
	*dest = *src;
    if(src->indicator != -1) {
		dest->data = (unsigned char*)malloc(src->octet_length);
		memcpy(dest->data, src->data, src->octet_length);
    }
    return dest;
}

}
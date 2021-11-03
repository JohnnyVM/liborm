#ifndef LIBORM_DATABASE_PARAMS_H
#define LIBORM_DATABASE_PARAMS_H

struct database_params {
	char dialect[64];
	char driver[64];
	char username[64];
	char password[64];
	char host[64];
	int port;
	char database[64];
	int flags;
};

#endif

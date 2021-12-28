#ifndef LIBORM_DRIVER_ORACLE_CONNECTION_DATA_H
#define LIBORM_DRIVER_ORACLE_CONNECTION_DATA_H

/** For avoid compilations problem if the header used in stadn alone mode */
#if !defined(ORA_PROC)
typedef void* sql_context;
#endif

struct oracle_connection_data {
	/*@{*/
	char user[128]; /**< User */
	char password[128]; /**< Password */
	unsigned char dbname[32]; /**< database name */
	unsigned char connect_string[128]; /**< Conection string */
	sql_context ctx; /**< Thread context, required for multithread connectionss */
	unsigned char input_descriptor[32]; /**< Necesary string for identify a descriptor */
	unsigned char output_descriptor[32]; /**< Necesary string for identify a descriptor */
};

#endif

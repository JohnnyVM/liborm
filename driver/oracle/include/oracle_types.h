#ifndef LIBORM_DRIVER_PRIVATE_ORACLE_TYPES_HPP
#define LIBORM_DRIVER_PRIVATE_ORACLE_TYPES_HPP

#define INDICATOR_NAME_LENGTH 129

#ifdef __cplusplus
extern "C" {
#endif

enum sql_code {
	// positive ansi types
	ORA_CHARACTER = 1,
	ORA_NUMBER = 2,
	ORA_CHARACTER_VARYING = 12,
	ORA_DATE = 9,
	ORA_DECIMAL = 3,
	ORA_DOUBLE_PRECISION = 8,
	ORA_FLOAT = 6,
	ORA_INTEGER = 4,
	ORA_REAL = 7,
	ORA_SMALLINT = 5,
	// Negative for ORACLE types
	ORA_VARCHAR2 = -1, /**< char[n] */
	ORA_ORACLE_NUMBER = -2, /**< char[n] (n<=22) */
	//ORACLE_INTEGER = -1, /**< float */
	ORA_ORACLE_FLOAT = -4, /**< float */
	ORA_STRING = -5, /**< char[n+1] */
	ORA_ORACLE_VARCHAR = -9, /**< char[n+2] */
	ORA_BINARY_FLOAT = -100,
	ORA_BINARY_DOUBLE = -101,
	ORA_ORACLE_DATE = -12,
	// ...
};

struct ora_database_type {
	enum sql_code type;
	int length; // length in nchar
	short returned_length;
	int octet_length; // length in bytes, use this, for allocate
	short returned_octet_length;
	int precision;
	int scale;
	/**< When the returned value is -127 the item being
	described is not initialized and is NULL in the data dictionary */
	int nullable; // 0 no null posible, 1 null posible
	short indicator;
	char name[INDICATOR_NAME_LENGTH]; // column name
	char* character_set_name;
	unsigned char* data;
};

// in C23 move this to [[attribute]]
__attribute__((nothrow, warn_unused_result)) struct ora_database_type* ora_database_type_clone(struct ora_database_type *result);
__attribute__((nothrow, warn_unused_result)) struct ora_database_type* ora_database_type_param_clone(struct ora_database_type *result);
__attribute__((nothrow)) void free_ora_database_type(struct ora_database_type* result);

#ifdef __cplusplus
}
#endif

#endif

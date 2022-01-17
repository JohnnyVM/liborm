#ifndef LIBORM_CONNECTION_STATEMENT_H
#define LIBORM_CONNECTION_STATEMENT_H

#include <stdlib.h>
#include "connection/types.h"

#ifndef __cplusplus

typedef struct Statement Statement;

#else

#include <memory>
#include <string>
#include <vector>

#include "liborm/type/engine.h" 

/**
 * \brief Dummy class for allow bind params
 * 
 */
struct Statement {
	Statement(const Statement&) = delete;
	Statement& operator=(const Statement&) = delete;
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	Statement(const T& _arg) : statement(std::string(_arg)) {}
	const std::string statement;
	std::vector<std::shared_ptr<const TypeEngine>> params;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

void free_statement(Statement* stmt);

/* This list of function bind parameters by position */
conn_state stmt_bind_null(Statement* stmt, unsigned pos, int val) __attribute__((nonnull));
conn_state stmt_bind_int(Statement* stmt, unsigned pos, int val) __attribute__((nonnull));
conn_state stmt_bind_char(Statement* stmt, unsigned pos, char* val, size_t)__attribute__((nonnull));

/* \todo This list of function bind parameters by name
conn_state stmt_bindn_int(Statement* stmt, unsigned, int val);
conn_state stmt_bindn_char(Statement* stmt, unsigned, char* val, size_t); */

#ifdef __cplusplus
}
#endif

#endif


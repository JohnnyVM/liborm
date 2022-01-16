#include <memory>

#include "liborm/type/types.hpp"
#include "liborm/connection/statement.h"

void free_statement(Statement* stmt) {
	delete stmt;
}

conn_state stmt_bind_char(Statement* stmt, unsigned pos, char* val, size_t size) {
    if(stmt->params.size() < pos + 1) {
        stmt->params.resize(pos + 1);
    }

    stmt->params[pos] = std::make_shared<orm::type::String>(size, val);
    return SQL_DONE;
}
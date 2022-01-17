#include <memory>

#include "liborm/type/types.hpp"
#include "liborm/connection/statement.h"

void free_statement(Statement* stmt) {
	delete stmt;
}

conn_state stmt_bind_null(Statement* stmt, unsigned pos) {
    if(stmt->params.size() < pos + 1) {
        stmt->params.resize(pos + 1);
    }

    stmt->params[pos] = std::make_shared<orm::type::Null>();
    return SQL_DONE;
}

conn_state stmt_bind_char(Statement* stmt, unsigned pos, char* val, size_t size) {
    if(stmt->params.size() < pos + 1) {
        stmt->params.resize(pos + 1);
    }
    assert(val);
    char ctmp[size];
    snprintf(ctmp, size, "%s", val);

    std::string stmp(ctmp);
    stmt->params[pos] = std::make_shared<orm::type::String>(val);
    return SQL_DONE;
}
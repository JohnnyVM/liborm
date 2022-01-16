#ifndef LIBORM_CONNECTION_CONNECTION_HPP
#define LIBORM_CONNECTION_CONNECTION_HPP

#include <tuple>
#include <memory>
#include <cassert>
#include <vector>
#include <initializer_list>

#include "liborm/utils/movable_il.hpp"
#include "connection/statement.h"
#include "connection/types.h"
#include "type/engine.h"

class Cursor;

/**
 * AConnection to the DBAPI
 */
class Connection {
	public:
	virtual ~Connection() = default;
	Connection& operator=(const Connection&) = delete;
	[[nodiscard]] virtual conn_state close() = 0;
	[[nodiscard]] virtual conn_state begin() = 0;
	[[nodiscard]] virtual conn_state commit() = 0;
	[[nodiscard]] virtual conn_state rollback() = 0;

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	[[nodiscard]] std::tuple<std::unique_ptr<Cursor>, conn_state> execute(const T& _stmt){
		std::vector<std::vector<std::shared_ptr<const TypeEngine>>>rows;
		std::vector<std::shared_ptr<const TypeEngine>>row;
		rows.emplace_back(row);
		std::string stmt = std::string(_stmt);
		return execute(stmt, rows);
	}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	[[nodiscard]] std::tuple<std::unique_ptr<Cursor>, conn_state> execute(
			const T& _stmt, std::initializer_list<std::shared_ptr<const TypeEngine>>list) {
		std::vector<std::vector<std::shared_ptr<const TypeEngine>>>rows;
		std::vector<std::shared_ptr<const TypeEngine>>row;
		std::string stmt = std::string(_stmt);
		for(std::shared_ptr<const TypeEngine> el : list) {
			row.emplace_back(el);
		}
		rows.push_back(row);
		return execute(stmt, rows);
	}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	[[nodiscard]] std::tuple<std::unique_ptr<Cursor>, conn_state> execute(
			const T& _stmt, std::initializer_list<std::initializer_list<std::shared_ptr<const TypeEngine>>>list){
		std::string stmt = std::string(_stmt);
		std::vector<std::vector<std::shared_ptr<const TypeEngine>>> rows;
		std::vector<std::shared_ptr<const TypeEngine>>row;
		for(std::initializer_list<std::shared_ptr<const TypeEngine>> l : list) {
			assert(list.begin()->size() == l.size());
			row.clear();
			for(std::shared_ptr<const TypeEngine> el : l) {
				row.emplace_back(el);
			}
			rows.emplace_back(row);
		}
		return execute(stmt, rows);
	}

	[[nodiscard]] virtual std::tuple<std::unique_ptr<Cursor>, conn_state> execute(
		const std::string& stmt, std::vector<std::vector<std::shared_ptr<const TypeEngine>>>list) = 0;
	[[nodiscard]] virtual bool is_open() = 0; /**< the connection is open */
	[[nodiscard]] virtual unsigned changes() = 0; /**< list of rows modified by the last statement */
	[[nodiscard]] virtual const char* error_message() = 0; /**< return latest connection error code as message database specific */
};

#endif

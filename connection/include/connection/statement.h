#ifndef LIBORM_CONNECTION_STATEMENT_H
#define LIBORM_CONNECTION_STATEMENT_H

#ifndef __cplusplus

typedef struct Statement Statement;

#else

#include <queue>
#include <variant>
#include <memory>
#include <string>
#include <unordered_map>

#include "type/engine.h" 

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
	std::queue<std::unordered_map<std::variant<unsigned, std::string>, std::unique_ptr<TypeEngine>>> params;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif


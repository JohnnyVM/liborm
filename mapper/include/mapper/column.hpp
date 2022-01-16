#ifndef LIBORM_MAPPER_COLUMN_HPP
#define LIBORM_MAPPER_COLUMN_HPP

#include <type_traits>
#include <cstdint>
#include <string>
#include <variant>
#include <cassert>
#include <memory>
#include <utility>

#include "mapper/table_element.hpp"
#include "liborm/type/engine.h"
#include "liborm/type/types.hpp"

namespace orm {

using default_type = std::variant<
	type::String,
	type::Numeric,
	type::Datetime>;

struct non_primary_key_nullable { bool primary_key; bool nullable; };

/**
 * \brief necesary definition to pass to class constructor
 */
class Column : public orm::TableElement {
	private:
	/* \todo default value */

	public:
	Column(const Column&) = delete;
	Column& operator=(const Column&) = delete;
	~Column() override {}
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	Column(const T& name, std::unique_ptr<TypeEngine>targ)
		: TableElement(std::string(name)),
		type(targ->clone()),
		primary_key(false),
		nullable(true),
		default_value(nullptr){}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	Column(const T& name, std::unique_ptr<TypeEngine>targ, bool pk, bool nulla, default_type(*dv)(void))
		: TableElement(std::string(name)),
		type(targ->clone()),
		primary_key(pk),
		nullable(nulla),
		default_value(dv)
	{assert(primary_key!=true || nullable == false);}

	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	Column(const T& name, std::unique_ptr<TypeEngine>targ, const struct non_primary_key_nullable& pknulla)
		: TableElement(std::string(name)),
		type(targ->clone()),
		primary_key(pknulla.primary_key),
		nullable(pknulla.nullable),
		default_value(nullptr)
	{assert(primary_key!=true || nullable == false);}

	std::unique_ptr<TypeEngine> type;
	bool primary_key = false;
	bool nullable = true;
	default_type(*default_value)(void); /* \todo */

};

/** Return a class Column */
std::unique_ptr<Column> column(const std::string& name, std::unique_ptr<TypeEngine>targ);
std::unique_ptr<Column> column(const std::string& name, std::unique_ptr<TypeEngine>targ, const struct non_primary_key_nullable& npk);

}

#endif

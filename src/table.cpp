#include "table.hpp"
#include "schema_element.hpp"
#include <initializer_list>
#include <string>

orm::Table::Table(const std::string& name, std::initializer_list<TableElement>) : orm::SchemaElement({name}) {

}

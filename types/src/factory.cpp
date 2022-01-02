#include <memory>

#include "type/factory.hpp"

std::unique_ptr<orm::TypeEngine> orm::TypeFactory::factory(const std::type_info& type) const {
    if(type == typeid(orm::type::String)) { // UGH...
        return String();
    }
    if(type == typeid(orm::type::Integer)) {
        return Integer();
    }
    if(type == typeid(orm::type::Numeric)) {
        return Numeric();
    }
    if(type == typeid(orm::type::Date)) {
        return Date();
    }
    if(type == typeid(orm::type::DateTime)) {
        return DateTime();
    }
    if(type == typeid(orm::type::Boolean)) {
        return Boolean();
    }
    if(type == typeid(orm::type::Float)) {
        return Float();
    }
    assert(!"Type not supported");
    return nullptr;
}


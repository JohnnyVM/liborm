cmake_minimum_required(VERSION 3.20)

project(types VERSION 0.1 DESCRIPTION "liborm types library")

configure_file(version.h.in include/types/version.h)

add_library(types STATIC
	src/factory.cpp
	src/engine.cpp
	src/numeric.cpp
	src/string.cpp
	src/datetime.cpp
	src/types.cpp)

target_include_directories(types PUBLIC
	include
)

install(TARGETS types DESTINATION lib)
install(DIRECTORY include/type DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

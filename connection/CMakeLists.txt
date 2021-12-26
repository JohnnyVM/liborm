cmake_minimum_required(VERSION 3.20)

project(connection VERSION 0.1 DESCRIPTION "connection interface")

configure_file(include/version.h.in include/connection/version.h)

add_library(connection STATIC
	src/connection.cpp
	src/cursor.cpp)

target_include_directories(connection PUBLIC
	include)

install(TARGETS connection DESTINATION lib)
install(DIRECTORY include DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

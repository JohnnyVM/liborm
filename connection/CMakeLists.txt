cmake_minimum_required(VERSION 3.20)

project(connection VERSION 0.1 DESCRIPTION "connection interface")

configure_file(include/version.h.in include/liborm/connection/version.h)

add_library(connection STATIC
	src/connection.cpp
	src/statement.cpp
	src/cursor.cpp)

target_include_directories(connection PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	$<INSTALL_INTERFACE:include/>
)

target_link_libraries(connection types utils)

install(TARGETS connection EXPORT connectionTargets DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)
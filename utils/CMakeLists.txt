cmake_minimum_required(VERSION 3.20)

project(utils VERSION 0.1 DESCRIPTION "liborm utils library")

configure_file(version.h.in include/liborm/utils/version.h)

add_library(utils STATIC
	src/utils.cpp)

target_include_directories(utils PUBLIC
	include
)

install(TARGETS utils DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

cmake_minimum_required(VERSION 3.20)

project(mapper VERSION 0.1 DESCRIPTION "liborm mapper library")

configure_file(version.h.in include/mapper/version.h)

add_library(mapper STATIC
	src/column.cpp
	src/table.cpp)

target_include_directories(mapper PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	$<INSTALL_INTERFACE:include/>
)

target_link_libraries(mapper types utils)

install(TARGETS mapper DESTINATION lib)
install(DIRECTORY include DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

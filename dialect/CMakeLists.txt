cmake_minimum_required(VERSION 3.20)

project(dialect VERSION 0.1 DESCRIPTION "liborm dialect library")

configure_file(version.h.in include/dialect/version.h)

add_library(dialect STATIC)

target_include_directories(dialect PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	$<INSTALL_INTERFACE:include/>
)

target_link_libraries(dialect types)

install(TARGETS dialect DESTINATION lib)
install(DIRECTORY include DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

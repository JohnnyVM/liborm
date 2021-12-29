cmake_minimum_required(VERSION 3.20)

project(engine VERSION 0.1 DESCRIPTION "define a database connection")

configure_file(include/version.h.in include/engine/version.h)

add_library(engine STATIC
	src/engine.cpp
	src/create_engine.cpp
	src/uri.cpp
)

target_include_directories(engine PUBLIC
	include
)

target_link_libraries(engine types connection)

if(POSTGRES)
target_link_libraries(engine postgres)
add_compile_definitions(POSTGRES)
endif()

if(ORACLE)
target_link_libraries(engine oracle)
add_compile_definitions(ORACLE)
endif()

install(TARGETS engine DESTINATION lib)
install(DIRECTORY engine DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

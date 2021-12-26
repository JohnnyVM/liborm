cmake_minimum_required(VERSION 3.20)

find_package(PostgreSQL REQUIRED)

set(driver postgres)
project(${driver} VERSION 0.1 DESCRIPTION "Postgres driver")

configure_file(include/version.h.in include/driver/postgres/version.h)

add_library(${driver} STATIC
	src/postgres.cpp
)
target_include_directories(${driver} PUBLIC
	include
	${PostgreSQL_INCLUDE_DIRS}
)

find_package(PostgreSQL REQUIRED)
target_link_libraries(${driver} connection engine ${PostgreSQL_LIBRARIES})
target_link_directories(${driver} PRIVATE ${PostgreSQL_LIBRARY_DIRS})

install(TARGETS ${driver}  DESTINATION lib)
install(DIRECTORY include DESTINATION include)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include
	DESTINATION include)

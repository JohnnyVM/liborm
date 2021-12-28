cmake_minimum_required(VERSION 3.20)

set(driver oracle)
project(${driver} VERSION 0.1 DESCRIPTION "Oracle driver")

configure_file(include/version.h.in include/driver/oracle/version.h)

set(PROC_SOURCES
	src/allocate_descriptor_global.pc
	src/commit.pc
	src/driver_ora_cursor.pc
	src/close.pc
	src/ora_connect.pc)

get_target_property (CONNECTION_INCLUDE_DIRS connection INCLUDE_DIRECTORIES)
get_target_property (TYPES_INCLUDE_DIRS types INCLUDE_DIRECTORIES)
set(INCLUDE_DIRS ${CONNECTION_INCLUDE_DIRS} ${TYPES_INCLUDE_DIRS})
list(TRANSFORM INCLUDE_DIRS PREPEND "INCLUDE=")
list(JOIN INCLUDE_DIRS " " INCLUDE_STRING)

foreach(proc_source ${PROC_SOURCES})
	cmake_path(GET proc_source STEM proc_name)
	add_custom_command(
		COMMAND proc CONFIG=${PROJECT_SOURCE_DIR}/proc.cfg INCLUDE=${PROJECT_SOURCE_DIR}/private INCLUDE=${PROJECT_SOURCE_DIR}/include ${INCLUDE_DIRS} iname=${PROJECT_SOURCE_DIR}/${proc_source} oname=${CMAKE_CURRENT_BINARY_DIR}/${proc_name}.c
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${proc_name}.c ${PROJECT_SOURCE_DIR}/src/${proc_name}.lis
		DEPENDS ${proc_source}
		VERBATIM)
	set(C_GENERATED ${C_GENERATED} ${CMAKE_CURRENT_BINARY_DIR}/${proc_name}.c)
endforeach()

set_source_files_properties(${C_GENERATED} PROPERTIES GENERATED 1)
set_source_files_properties(${C_GENERATED} PROPERTIES COMPILE_OPTIONS
		"-Wno-padded;-Wno-missing-field-initializers;-Wno-unused-const-variable;-Wno-unused-variable;-Wno-shadow")

add_library(${driver} STATIC
	${C_GENERATED}
	src/factory.cpp
	src/number_to_Decimal.c
	src/cursor.cpp
	src/engine.cpp
	src/connection.cpp)

target_include_directories(${driver}
	PUBLIC include $ENV{ORACLE_HOME}/sdk/include)

target_link_libraries(${driver} connection engine types -lclntsh)
target_link_directories(${driver} PUBLIC $ENV{ORACLE_HOME}/lib)

install(TARGETS ${driver}  DESTINATION lib)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

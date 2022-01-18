if(DEFINED ENV{CPPUTEST_HOME})
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

if(ORACLE)
	set(OPTIONAL_SOURCES ${OPTIONAL_SOURCES} 
		src/driver_oracle.cpp
		src/driver_oracle_c.c)
endif()

if(POSTGRES)
	set(OPTIONAL_SOURCES ${OPTIONAL_SOURCES} src/driver_postgres.cpp)
endif()

add_executable(tests
	src/uri.cpp
	src/driver.cpp
	src/driver_c.c
	src/numeric.cpp
	src/string.cpp
	src/type_engine.cpp
	src/mapper.cpp
	${OPTIONAL_SOURCES}
	src/main.cpp)

target_link_libraries(tests
	PRIVATE orm ${CPPUTEST_LDFLAGS})
target_include_directories(tests PRIVATE ${CPPUTEST_INCLUDE_DIRS})
target_link_directories(tests PRIVATE ${CPPUTEST_LIBRARIES})

if(ORACLE)
	target_compile_definitions(tests PUBLIC ORACLE)
endif()

if(RUN_TESTS)
add_custom_command(TARGET tests COMMAND ./tests POST_BUILD)
endif()

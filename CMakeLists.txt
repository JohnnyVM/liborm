cmake_minimum_required(VERSION 3.20)

project(orm VERSION 0.1 DESCRIPTION "liborm library")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(liborm_VERSION 0.0.1)

option(CHECK_MEMORY "Build with memory sanitize support" OFF)
option(CHECK_THREADS "Build with memory sanitize threads support (todo)" OFF)
option(POSTGRES "Build postgresql support" OFF)
option(ORACLE "Build oracle support" OFF)
option(SQLITE "Build sqlite support" OFF)
option(MYSQL "Build mysql support" OFF)
option(TESTS "Build the tests" OFF)
option(RUN_TESTS "Build the tests" ON)
option(COVERAGE "Coverage report added" OFF)
option(DOXYGEN "Generate doxygen documentation" OFF)

configure_file(version.h.in include/version.h)

add_compile_options(-Wall -Wextra -Werror -fno-common -Wformat -Wformat-truncation -Wshadow -Wundef -Wconversion)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions")

if(CHECK_MEMORY)
add_compile_options(-fsanitize=undefined -fsanitize=address -fsanitize=leak -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize-recover=all)
add_link_options(-fsanitize=undefined -fsanitize=address -fsanitize=leak -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize-recover=all)
elseif(CHECK_THREADS)
add_compile_options(-fsanitize=undefined -fsanitize=thread -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize-recover=all)
add_link_options(-fsanitize=undefined -fsanitize=thread -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize-recover=all)
endif()

if(COVERAGE)
# CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(CodeCoverage)
append_coverage_compiler_flags("-fprofile-arcs -ftest-coverage")
setup_target_for_coverage_gcovr_html(
	NAME coverage
	EXECUTABLE tests
	BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
	EXCLUDE "${PROJECT_SOURCE_DIR}/tests/*")
endif()

if(DOXYGEN)
find_package(Doxygen
             OPTIONAL_COMPONENTS dot mscgen dia)
doxygen_add_docs(doxygen ALL)
endif()

set(C_STANDARD 17)
set(CMAKE_CXX_STANDARD ${C_STANDARD})
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(engine)
add_subdirectory(connection)
add_subdirectory(mapper)
add_subdirectory(types)
add_subdirectory(utils)

add_library(orm STATIC
	src/liborm.cpp)

include(GenerateExportHeader)

target_link_libraries(orm PUBLIC engine connection mapper types)

if(TESTS)
add_subdirectory(tests)
endif()

if(POSTGRES)
	set(liborm_targets ${liborm_targets} postgres)
	add_subdirectory(driver/postgres)
endif()

if(ORACLE)
	set(liborm_targets ${liborm_targets} oracle)
	add_subdirectory(driver/oracle)
endif()

generate_export_header(orm)
set_property(TARGET orm PROPERTY VERSION ${liborm_VERSION})

install(TARGETS orm engine connection mapper types utils ${liborm_targets} EXPORT libormTargets
	DESTINATION lib)
install(DIRECTORY
		${PROJECT_BINARY_DIR}/include/
	DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${liborm_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${liborm_VERSION_MINOR}")
include(CPack)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/liborm/libormConfigVersion.cmake"
  VERSION ${liborm_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT libormTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/liborm/liborm.cmake"
  NAMESPACE liborm::)
configure_file(cmake/libormConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/liborm/libormConfig.cmake"
  COPYONLY)

set(ConfigPackageLocation cmake/liborm)
install(EXPORT libormTargets
	FILE
	libormTargets.cmake
	NAMESPACE
		liborm::
	DESTINATION
		${ConfigPackageLocation})
install(
  FILES
    cmake/libormConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/liborm/libormConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel)
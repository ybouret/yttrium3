# CMake at top-level
cmake_minimum_required(VERSION 3.18)

# global project
project(yttrium3)
include(../etc/y.cmake)

# generating documentation
find_program(DOX doxygen DOC "Doxygen")
cmake_print_variables(DOX)
if( "${DOX}" STREQUAL "DOX-NOTFOUND")
    message( STATUS "no doxygen")
else()
    message( STATUS "found ${DOX}")
    add_custom_target(dox ${DOX} -q WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

set(Y_UnitTests "")
add_subdirectory(root)
cmake_print_variables(Y_UnitTests)


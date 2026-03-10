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

# prepare unit tests
set(Y_UnitTests "")

# add components
add_subdirectory(root)

# regression with all unit tests
cmake_print_variables(Y_UnitTests)
if( NOT "" STREQUAL "${Y_UnitTests}")
    add_custom_target(regression
    DEPENDS ${Y_UnitTests})
endif()


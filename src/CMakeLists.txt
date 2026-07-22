################################################################################
#
#
# CMake at top-level
#
#
################################################################################
cmake_minimum_required(VERSION 3.11)

set(Y_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set(Y_ETC_DIR ${Y_SRC_DIR}/../etc)
set(CMAKE_INSTALL_PREFIX ${Y_SRC_DIR}/../sdk)

################################################################################
#
#
# Global project
#
#
################################################################################
project(yttrium3)
include(${Y_ETC_DIR}/y.cmake)

################################################################################
#
#
# Generating documentation
#
#
################################################################################
find_program(DOX doxygen DOC "Doxygen")
cmake_print_variables(DOX)
if( "${DOX}" STREQUAL "DOX-NOTFOUND")
    message( STATUS "no doxygen")
else()
    message( STATUS "found ${DOX}")
    add_custom_target(dox ${DOX} -q WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

################################################################################
#
#
# prepare unit tests
#
#
################################################################################
set(Y_UnitTests "")

################################################################################
#
#
# Add third party
#
#
################################################################################
add_subdirectory(y)

################################################################################
#
#
# Add components
#
#
################################################################################
add_subdirectory(root)
add_subdirectory(mkl)
add_subdirectory(lua++)
add_subdirectory(chem)
add_subdirectory(ink)

################################################################################
#
#
# Add CLI tools
#
#
################################################################################
add_subdirectory(cli)


################################################################################
#
#
# Other
#
#
################################################################################
add_subdirectory(python)


################################################################################
#
#
# regression with all unit tests
#
#
################################################################################
cmake_print_variables(Y_UnitTests)
if( NOT "" STREQUAL "${Y_UnitTests}")
    add_custom_target(regression
    DEPENDS ${Y_UnitTests})
endif()
################################################################################
#
#
# Global Settings
#
#
################################################################################
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS    ON)
set(CMAKE_SKIP_PREPROCESSED_SOURCE_RULES ON)
set(CMAKE_SKIP_ASSEMBLY_SOURCE_RULES     ON)
include(CMakePrintHelpers)
set(CMAKE_INSTALL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../sdk")

################################################################################
#
#
# Finding Compiler word bits
#
#
################################################################################
cmake_print_variables(CMAKE_SIZEOF_VOID_P)

set(Y_KNOWN_BITS OFF)

if( "2" STREQUAL "${CMAKE_SIZEOF_VOID_P}")
        set(Y_KNOWN_BITS ON)
        set(Y_BITS 16)
        set(Y16 ON)
endif()

if( "4" STREQUAL "${CMAKE_SIZEOF_VOID_P}")
        set(Y_KNOWN_BITS ON)
        set(Y_BITS 32)
        set(Y32 ON)
endif()

if( "8" STREQUAL "${CMAKE_SIZEOF_VOID_P}")
        set(Y_KNOWN_BITS ON)
        set(Y_BITS 32)
        set(Y64 ON)
endif()

if(NOT Y_KNOWN_BITS)
        message( FATAL_ERROR "unknown sizeof(void*)" )
endif()

################################################################################
#
#
# Detecting the CMAKE_BUILD_TYPE
#
#
################################################################################
if("" STREQUAL "${CMAKE_BUILD_TYPE}")
        set(CMAKE_BUILD_TYPE "Debug")
endif()

# selecting build type
set(Y_DEBUG   TRUE)
set(Y_RELEASE FALSE)
set(Y_BUILD_TYPE_IS_DEFINED FALSE)

if( "Debug" STREQUAL "${CMAKE_BUILD_TYPE}")
        # default
        set(Y_BUILD_TYPE_IS_DEFINED TRUE)
endif()

if( "Release" STREQUAL "${CMAKE_BUILD_TYPE}")
        # release
        set(Y_BUILD_TYPE_IS_DEFINED TRUE)
        set(Y_DEBUG FALSE)
        set(Y_RELEASE TRUE)
endif()

if(NOT Y_BUILD_TYPE_IS_DEFINED)
        message( FATAL_ERROR "CMAKE_BUILD_TYPE!=[Debug|Release]")
endif()

cmake_print_variables(CMAKE_BUILD_TYPE)

################################################################################
#
#
# Y_Platform and global platform flags
#
#
################################################################################
cmake_print_variables(CMAKE_SYSTEM_NAME)

string( TOLOWER "${CMAKE_SYSTEM_NAME}"      Y_Platform)
cmake_print_variables(Y_Platform)

if( "Linux" STREQUAL "${CMAKE_SYSTEM_NAME}" )
        set(Y_Linux ON)
endif()

if( "FreeBSD" STREQUAL "${CMAKE_SYSTEM_NAME}" )
        set(Y_FreeBSD ON)
endif()

if( "SunOS" STREQUAL "${CMAKE_SYSTEM_NAME}" )
        set(Y_SunOS ON)
endif()

if( "Windows" STREQUAL "${CMAKE_SYSTEM_NAME}" )
        set(Y_Windows ON)
endif()

################################################################################
#
#
# Y_Machine
#
#
################################################################################
cmake_print_variables(CMAKE_SYSTEM_PROCESSOR)

string( TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" Y_Machine)

if(Y_SunOS)
        set(Y_Machine "i86pc")
endif()

if(Y_Windows)
        if(Y32)
                set(Y_Machine "i686")
        endif()
endif()


cmake_print_variables(Y_Machine)


################################################################################
#
#
# Y_CC and Y_CXX with version
#
#
################################################################################
get_filename_component(Y_CC ${CMAKE_C_COMPILER} NAME_WE)
get_filename_component(Y_CXX ${CMAKE_CXX_COMPILER} NAME_WE)
cmake_print_variables(CMAKE_C_COMPILER)
cmake_print_variables(CMAKE_CXX_COMPILER)
cmake_print_variables(Y_CC Y_CXX)

set(Y_CC_MAJOR 0)
set(Y_CC_MINOR 0)

cmake_print_variables(CMAKE_C_COMPILER_VERSION)
string(REPLACE "." ";" Y_CC_VERSION ${CMAKE_C_COMPILER_VERSION})
list(GET Y_CC_VERSION 0 Y_CC_MAJOR)
list(GET Y_CC_VERSION 1 Y_CC_MINOR)
cmake_print_variables(Y_CC_MAJOR Y_CC_MINOR)

set(Y_KNOWN_COMPILER FALSE)

################################################################################
#
# configuration for gcc/g++
#
################################################################################
if("${Y_CC}" MATCHES "gcc.*")
        message( STATUS "Using GNU Compilers")
        set(Y_KNOWN_COMPILER TRUE)
        set(Y_GNU TRUE)
        string( APPEND CMAKE_C_FLAGS " -pipe -Wall -Wextra -std=c99")
        string( APPEND CMAKE_CXX_FLAGS " -pipe -Wall -Wextra -Weffc++")
        if( "${Y_CC_MAJOR}" LESS "7" )
                string( APPEND CMAKE_CXX_FLAGS " -std=c++0x")
                string( APPEND CMAKE_C_FLAGS   " -std=c99")
        endif()
        if(APPLE)
                string( APPEND CMAKE_CXX_FLAGS " -D_Alignof=sizeof")
        endif()
endif()

################################################################################
#
# configuration for clang/clang++
#
################################################################################
if("${Y_CC}" MATCHES "clang.*")
        message( STATUS "Using Clang Compilers")
        set(Y_KNOWN_COMPILER TRUE)
        set(Y_CLANG TRUE)
        string( APPEND CMAKE_C_FLAGS   " -pipe -Wall -Wextra")
        string( APPEND CMAKE_CXX_FLAGS " -pipe -Wall -Wextra -Weffc++ -std=c++11")
endif()



################################################################################
#
# configuration for icc/icpc or icx/icpx
#
################################################################################
if("${Y_CC}" MATCHES "ic.*")
        message( STATUS "Using Intel Compilers")
        set(Y_KNOWN_COMPILER TRUE)
        set(Y_ICC TRUE)
        string( APPEND CMAKE_C_FLAGS   " -Wall")
        string( APPEND CMAKE_CXX_FLAGS " -Wall")
        if( "${Y_CC_MAJOR}" LESS_EQUAL "13" )
                string( APPEND CMAKE_CXX_FLAGS " -std=c++0x")
        endif()
endif()

################################################################################
#
# configuration for Microsoft
#
################################################################################
if("${Y_CC}" STREQUAL "cl")
        message( STATUS "Using Microsoft Compilers")
        set(Y_KNOWN_COMPILER TRUE)
        set(Y_MSC TRUE)
        string( APPEND CMAKE_C_FLAGS   " -Wall -nologo -wd4668")
        string( APPEND CMAKE_CXX_FLAGS " -Wall -nologo -EHsc -wd4668")
endif()

if(NOT Y_KNOWN_COMPILER)
        message( FATAL_ERROR "Unknown Compiler ${Y_CC}")
endif()

################################################################################
#
# specific platform flags
#
################################################################################
if(Y_Linux OR Y_SunOS OR Y_FreeBSD)
        if(Y_GNU OR Y_CLANG OR Y_ICC)
                string( APPEND CMAKE_C_FLAGS " -fPIC")
                string( APPEND CMAKE_CXX_FLAGS " -fPIC")
        endif()
endif()


cmake_print_variables(CMAKE_C_FLAGS)
cmake_print_variables(CMAKE_CXX_FLAGS)



################################################################################
#
#
# Creating Library THE_LIB using files or subdir
#
#
################################################################################
function(Y_CreateLibrary THE_LIB)
        message(STATUS "Create Library <${THE_LIB}>")
        # local Sources, Private Sources and Headers
        set(SRC "")
        set(PRV "")
        set(HDR "")
        list(SORT ARGN)
        foreach(arg IN LISTS ARGN)
                set(path "${CMAKE_CURRENT_SOURCE_DIR}/${arg}")
                if(IS_DIRECTORY ${path})
                        # processing subdirectory
                        message( STATUS "   |_[${arg}]")
                        file( GLOB src "${arg}/*.cpp" "${arg}/*.c" )
                        file( GLOB prv "${arg}/*.hxx")
                        file( GLOB hdr "${arg}/*.hpp" "${arg}/*.h")
                        list(SORT src)
                        list(SORT prv)
                        list(SORT hdr)
                        source_group(${arg} FILES ${src} ${prv} ${hdr})
                        list( APPEND SRC ${src})
                        list( APPEND PRV ${prv})
                        list( APPEND HDR ${hdr})
                        install( FILES  ${hdr} DESTINATION include/${arg})
                else()
                        # assuming regular file
                        message( STATUS "   --[${arg}]")
                        message( FATAL_ERROR "need to code single file append...")
                endif()
        endforeach()
        add_library(${THE_LIB} STATIC ${SRC} ${HDR} ${PRV})
        install( TARGETS ${THE_LIB} ARCHIVE)
endfunction()

################################################################################
#
#
# Default Linking Libraries and Flags
#
#
################################################################################
function(Y_LinkLibraries THE_EXE)
        set(THE_LIBS "")

        # forward extra libraries
        list(APPEND THE_LIBS ${ARGN} )
        list(APPEND THE_LIBS "y")
        #list(APPEND THE_LIBS "y-z")
        #list(APPEND THE_LIBS "y-bz2")

        if(Y_Linux OR Y_FreeBSD)
                list( APPEND THE_LIBS "pthread" )
        endif()
        if(Y_Linux)
                list( APPEND THE_LIBS "rt" )
                list( APPEND THE_LIBS "dl" )
        endif()

        target_link_libraries(${THE_EXE} ${THE_LIBS})
endfunction()


################################################################################
#
#
# Creating a test program and define Y_Test to use Y_UTEST()
#
#
################################################################################
function(Y_CreateTest THE_LIB)
        set(THE_TEST "test-${THE_LIB}")
        message( STATUS "Create Test <${THE_TEST}>")
        # top-level sources
        set(SRC main.cpp)
        file( GLOB src "test-*.cpp" "*.hpp")
        #cmake_print_variables(src)
        #message( FATAL_ERROR "stop")
        list( APPEND SRC ${src} )
        list( SORT SRC )
        # sub-dir sources
        list(SORT ARGN)
        foreach(SUBDIR IN LISTS ARGN)
                message( STATUS "    [${SUBDIR}]")
                file( GLOB src "${SUBDIR}/*.cpp")
                list( SORT src )
                list( APPEND SRC ${src})
                list( SORT SRC )
                source_group(${SUBDIR} FILES ${src})
        endforeach()

        # gather
        add_executable(${THE_TEST} ${SRC})
        set(Y_Test ${THE_TEST} PARENT_SCOPE)

        # create unit tests
        add_custom_target("u${THE_TEST}" 
                COMMAND ${CMAKE_CTEST_COMMAND}
                DEPENDS ${THE_TEST}
                )
endfunction()

################################################################################
#
#
# create a new test
#
#
################################################################################
function(Y_UTEST THE_NAME)
        string(REPLACE ":" "_" THE_TEST "${THE_NAME}")
        add_test(${THE_NAME} ${Y_Test} ${THE_TEST} ${ARGN})
        message(STATUS "    <${THE_NAME}>")
endfunction()

################################################################################
#
#
# Register "utest-THE_LIB" tor Y_UnitTests
#
#
################################################################################

macro(Y_Regression THE_LIB)
        set(_UnitTests ${Y_UnitTests})
        list(APPEND _UnitTests "utest-${THE_LIB}")
        set(Y_UnitTests ${_UnitTests} PARENT_SCOPE)
endmacro()



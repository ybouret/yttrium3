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

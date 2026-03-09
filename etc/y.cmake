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

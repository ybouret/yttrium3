project(bzip2 C)

add_definitions(-D_FILE_OFFSET_BITS=64)
string( REPLACE "-std=c99" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

if(Y_MSC)
    string( APPEND CMAKE_C_FLAGS " -wd4711 -wd4127 -wd5045 -wd4668 -wd4996 -wd4100 -wd4710 -wd4242 -wd4244 -wd4820 -wd4267")
endif()

set(bz2SRCS
blocksort.c  
huffman.c    
crctable.c   
randtable.c  
compress.c  
decompress.c 
bzlib.c)

add_library(y-bz2 STATIC ${bz2SRCS})
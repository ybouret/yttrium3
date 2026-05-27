project(bzip2 C)

add_definitions(-D_FILE_OFFSET_BITS=64)
string( REPLACE "-std=c99" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

set(bz2SRCS
blocksort.c  
huffman.c    
crctable.c   
randtable.c  
compress.c  
decompress.c 
bzlib.c)

add_library(y-bz2 STATIC ${bz2SRCS})
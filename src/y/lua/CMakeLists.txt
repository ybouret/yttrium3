project(y-lua C)

# set OBJS from src/Makefile
set(OBJS
lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o
lauxlib.o lbaselib.o lcorolib.o ldblib.o liolib.o lmathlib.o loadlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o linit.o)

# create sources
set(SRCS "")
foreach(obj IN ITEMS ${OBJS})
    string( REPLACE ".o" ".c" src "${obj}")
    list( APPEND SRCS "src/${src}")
endforeach()

#cmake_print_variables(SRCS)

add_library(y-lua STATIC ${SRCS})

add_executable(y_lua src/lua.c)
target_link_libraries(y_lua y-lua m)


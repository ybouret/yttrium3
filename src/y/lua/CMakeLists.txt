project(y-lua C)

if(Y_MSC)
    string( APPEND CMAKE_C_FLAGS " -wd4310 -wd4709 -wd4820 -wd4668 -wd4710 -wd4711 -wd4701 -wd4702 -wd4324 -wd4774 -wd5045 -wd4061 -wd4191")
endif()

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
target_link_libraries(y_lua y-lua)

if(Y_SunOS OR Y_Linux OR Y_FreeBSD)
    target_link_libraries(y_lua m)
endif()

Y_ThirdParty(y_lua)


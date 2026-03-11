project(y)

include_directories(.)

Y_CreateLibrary(y
y
y/config
y/check
y/libc
y/core
y/random
y/system
y/memory
y/memory/small
y/utest)

add_subdirectory(tests)
Y_Regression(root)


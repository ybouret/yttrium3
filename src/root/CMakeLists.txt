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
y/utest)

add_subdirectory(tests)
Y_Regression(root)


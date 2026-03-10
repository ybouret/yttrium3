project(y)

include_directories(.)

Y_CreateLibrary(y
y
y/config
y/libc
y/core
y/random
y/utest)

add_subdirectory(tests)
Y_Regression(root)


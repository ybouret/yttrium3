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
y/concurrent
y/concurrent/singleton
y/calculus
y/type
y/memory
y/memory/small
y/ability
y/container
y/container/iter
y/utest)

add_subdirectory(tests)
Y_Regression(root)


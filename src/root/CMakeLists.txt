project(y)

include_directories(.)

Y_CreateLibrary(y
y
y/config
y/check
y/libc
y/libc/block
y/libc/str
y/xml
y/core
y/core/pool
y/core/list
y/random
y/system
y/system/wall-time
y/ascii
y/ascii/base64
y/format
y/concurrent
y/concurrent/nucleus
y/concurrent/sys
y/concurrent/singleton
y/concurrent/windows
y/calculus
y/type
y/memory
y/memory/type
y/memory/small
y/memory/page
y/memory/plastic
y/memory/allocator
y/ability
y/container
y/container/iter
y/pointer
y/utest
y/stream
y/object
)

add_subdirectory(tests)
Y_Regression(root)


Y_CreateTest(root
config
libc
core
system
memory/small)

Y_LinkLibraries(test-root)

enable_testing()

Y_UTEST(exception)

Y_UTEST(config:platform)

Y_UTEST(core:display)
Y_UTEST(core:rand)

Y_UTEST(libc:sort)
Y_UTEST(libc:strfmt)

Y_UTEST(system:error)
Y_UTEST(system:exception)
Y_UTEST(system:pid)

Y_UTEST(memory:small:chunk)




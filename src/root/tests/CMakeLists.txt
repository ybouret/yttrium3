Y_CreateTest(root
config
libc
core
system
calculus
type
concurrent
memory/small)

Y_LinkLibraries(test-root)

enable_testing()

Y_UTEST(exception)

Y_UTEST(config:platform)

Y_UTEST(core:display)
Y_UTEST(core:hsort)
Y_UTEST(core:hindx)
Y_UTEST(core:rand)
Y_UTEST(core:pool)
Y_UTEST(core:list)

Y_UTEST(libc:sort)
Y_UTEST(libc:strfmt)

Y_UTEST(system:error)
Y_UTEST(system:exception)
Y_UTEST(system:pid)

Y_UTEST(calculus:integer_log2)
Y_UTEST(calculus:base2)
Y_UTEST(calculus:meta2)
Y_UTEST(calculus:align)

Y_UTEST(type_ints)

Y_UTEST(concurrent:nucleus)
Y_UTEST(memory:small:chunk)
Y_UTEST(memory:small:arena)





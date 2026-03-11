Y_CreateTest(root
config
libc
core
system
calculus
type
memory/small)

Y_LinkLibraries(test-root)

enable_testing()

Y_UTEST(exception)

Y_UTEST(config:platform)

Y_UTEST(core:display)
Y_UTEST(core:rand)
Y_UTEST(core:pool)
Y_UTEST(core:list)

Y_UTEST(libc:sort)
Y_UTEST(libc:strfmt)

Y_UTEST(system:error)
Y_UTEST(system:exception)
Y_UTEST(system:pid)

Y_UTEST(calculus_integer_log2)
Y_UTEST(calculus_base2)
Y_UTEST(calculus_align)

Y_UTEST(type_ints)

Y_UTEST(memory:small:chunk)
Y_UTEST(memory:small:arena)





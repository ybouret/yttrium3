Y_CreateTest(root
config
libc
core)
Y_LinkLibraries(test-root)
Y_Regression(root)

enable_testing()

Y_UTEST(exception)

Y_UTEST(config:platform)

Y_UTEST(core:display)
Y_UTEST(core:rand)

Y_UTEST(libc:sort)
Y_UTEST(libc:strfmt)


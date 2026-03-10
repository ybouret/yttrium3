Y_CreateTest(root
config
libc
core)
Y_LinkLibraries(test-root)
Y_Regression(root)

enable_testing()

Y_UTEST(config:platform)

Y_UTEST(core:display)

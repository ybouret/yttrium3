Y_CreateTest(chem)

Y_LinkLibraries(test-chem y-chem y-lua++ y-lua)

enable_testing()

Y_UTEST(weasel)
Y_UTEST(aftermath)


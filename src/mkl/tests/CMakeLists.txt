Y_CreateTest(mkl
algebra)

Y_LinkLibraries(test-mkl y-mkl)
#target_link_libraries(test-root)

enable_testing()

Y_UTEST(algebra:lu)
Y_UTEST(algebra:adjoint)


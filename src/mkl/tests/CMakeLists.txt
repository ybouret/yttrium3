Y_CreateTest(mkl
algebra)

Y_LinkLibraries(test-mkl y-mkl)
#target_link_libraries(test-root)

enable_testing()

Y_UTEST(algebra:mmul)
Y_UTEST(algebra:rank)
Y_UTEST(algebra:lu)
Y_UTEST(algebra:adjoint)
Y_UTEST(algebra:ortho:space)
Y_UTEST(algebra:tridiag)
Y_UTEST(algebra:cyclic)
Y_UTEST(algebra:svd)

Y_UTEST(chem)


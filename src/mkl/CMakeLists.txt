include_directories(. ../root)

Y_CreateLibrary(y-mkl
y/mkl
y/mkl/algebra
y/mkl/interpolation
y/mkl/derivatives
y/mkl/root
)

add_subdirectory(tests)
Y_Regression(mkl)

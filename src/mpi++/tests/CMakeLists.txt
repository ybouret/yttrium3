Y_CreateTest(mpi++)
Y_LinkLibraries(test-mpi++ y-mpi++ ${MPI_C_LIBRARIES})

enable_testing()

Y_UTEST(excp)
#Y_UTEST(init)


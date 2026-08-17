include(../../etc/mpi.cmake)

if(MPI_FOUND)
include_directories(. ../root)

Y_CreateLibrary(y-mpi++
y/mpi++
)

add_subdirectory(tests)
#Y_Regression(mpi++)

endif(MPI_FOUND)



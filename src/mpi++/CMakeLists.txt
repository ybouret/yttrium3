include(../../etc/mpi.cmake)

if(MPI_FOUND)
include_directories(. ../root)
include_directories(${MPI_C_INCLUDE_DIRS})

Y_CreateLibrary(y-mpi++
y/mpi++
y/mpi++/api
)

add_subdirectory(tests)
#Y_Regression(mpi++)

endif(MPI_FOUND)



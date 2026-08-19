message(STATUS "    [[ Detecting MPI.... ]] ")

if(MINGW)
	message( STATUS "In MINGW" )
	set(MPI_FOUND OFF)
else()
	find_package(MPI)
endif()


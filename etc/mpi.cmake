
message(STATUS "")
message(STATUS "Detecting MPI, please wait.. ")
message(STATUS "")

if(MINGW)
	message( STATUS "In MINGW" )
	set(MPI_FOUND OFF)
	set(MPI_PATH "C:/Program Files (x86)/Microsoft SDKs/MPI")
	if(IS_DIRECTORY "${MPI_PATH}")
		message( STATUS "found ${MPI_PATH}" )
		set(MPI_FOUND ON)
                set(MPI_C_INCLUDE_DIRS "${MPI_PATH}/Include")
				if(Y32)
					set(MPI_C_LIBRARIES "${MPI_PATH}/Lib/x86/msmpi.lib")
				endif()

				if(Y64)
					set(MPI_C_LIBRARIES "${MPI_PATH}/Lib/x64/msmpi.lib")
				endif()

	else()
		message( STATUS "no ${MPI_PATH}" )
	endif()
else()
	# fallback to plain MPI from CMake
	find_package(MPI)
endif()


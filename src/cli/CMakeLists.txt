 
include_directories(../root)

message( STATUS )
message( STATUS "Preparing Command Line Interface utilities:")
macro(Y_CLI progname)
	message( STATUS "[+] <${progname}>")
	add_executable(${progname} "${progname}.cpp")
	Y_LinkLibraries(${progname} "${ARGN}")
endmacro()

Y_CLI(y_trunc)
Y_CLI(y_xctest)
if(APPLE)
Y_CLI(y_mp_needs)
endif()

message( STATUS )


 
include_directories(../root)


macro(Y_CLI progname)
	message( STATUS "    CLI:    <${progname}>")
	add_executable(${progname} "${progname}.cpp")
	Y_LinkLibraries(${progname} "${ARGN}")
endmacro()

Y_CLI(y_trunc)



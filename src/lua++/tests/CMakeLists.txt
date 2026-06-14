Y_CreateTest(lua++)

Y_LinkLibraries(test-lua++ y-lua++ y-lua)

set( HERE ${CMAKE_CURRENT_SOURCE_DIR} )

enable_testing()

Y_UTEST(state  ${HERE}/sample.lua)
Y_UTEST(function)


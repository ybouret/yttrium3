Y_CreateTest(json)

Y_LinkLibraries(test-json y-json)

set( HERE ${CMAKE_CURRENT_SOURCE_DIR} )
set( VDIR "${HERE}/../../../var")

enable_testing()

add_test(NAME db      COMMAND test-json compile "${VDIR}/db.js" )
add_test(NAME sample1 COMMAND test-json compile "${VDIR}/sample1.js" )
add_test(NAME sample2 COMMAND test-json compile "${VDIR}/sample2.js" )
add_test(NAME sample3 COMMAND test-json compile "${VDIR}/sample3.js" )
add_test(NAME sample4 COMMAND test-json compile "${VDIR}/sample4.js" )


set(third_party_list "")

# macro to add to list
macro(Y_ThirdParty)
    set(local_third_party ${third_party_list})
    foreach(tgt ${ARGN})
        #message(STATUS "---> ${tgt}" )
        list(APPEND local_third_party "${tgt}")
    endforeach()
    set(third_party_list ${local_third_party} PARENT_SCOPE)
endmacro()

set(ThirdPartyDir ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(zlib)
add_subdirectory(bzip2)
add_subdirectory(lua)
add_subdirectory(jbig)
add_subdirectory(jpeg)

cmake_print_variables(third_party_list)

add_custom_target(third_party
DEPENDS ${third_party_list})


include_directories(. ../root)

Y_CreateLibrary(y-chem
y/chemical
y/chemical/weasel
)

add_subdirectory(tests)

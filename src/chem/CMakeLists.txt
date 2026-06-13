include_directories(. ../root)

Y_CreateLibrary(y-chem
y/chemical
y/chemical/type
y/chemical/weasel
y/chemical/formula
y/chemical/reactive
)

add_subdirectory(tests)

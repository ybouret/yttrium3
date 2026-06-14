include_directories(. ../root)

Y_CreateLibrary(y-chem
y/chemical
y/chemical/type
y/chemical/weasel
y/chemical/formula
y/chemical/reactive
y/chemical/reactive/equilibrium
)

add_subdirectory(tests)

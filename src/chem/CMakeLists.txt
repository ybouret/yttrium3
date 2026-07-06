include_directories(. ../root ../mkl ../lua++ ../y/lua/src)

Y_CreateLibrary(y-chem
y/chemical
y/chemical/type
y/chemical/weasel
y/chemical/formula
y/chemical/reactive
y/chemical/reactive/equilibrium
y/chemical/plexus
y/chemical/plexus/conservation
y/chemical/plexus/conservation/law
y/chemical/plexus/combinatorics
)

add_subdirectory(tests)

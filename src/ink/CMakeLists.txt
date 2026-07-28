include_directories(. ../root)

Y_CreateLibrary(y-ink
y/ink
y/ink/histogram
y/ink/image
)

add_subdirectory(tests)
Y_Regression(ink)

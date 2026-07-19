
Y_CreateTest(ink)

Y_LinkLibraries(test-ink y-ink)

enable_testing()

Y_UTEST(broker)
Y_UTEST(bitmap)
Y_UTEST(pixmap)

#include "y/utest/driver.hpp"


Y_UTEST_DECL(3)
{
    Y_UTEST(exception);

    Y_UTEST(config_platform);


    Y_UTEST(core_display);
    Y_UTEST(core_rand);

    Y_UTEST(libc_sort);
    Y_UTEST(libc_strfmt);
    
}
Y_UTEST_EXEC()




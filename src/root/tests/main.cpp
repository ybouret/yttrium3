#include "y/utest/driver.hpp"


Y_UTEST_DECL(8)
{
    Y_UTEST(exception);

    Y_UTEST(config_platform);
    Y_UTEST(config_compiler);


    Y_UTEST(core_display);
    Y_UTEST(core_rand);
    Y_UTEST(core_pool);

    Y_UTEST(libc_sort);
    Y_UTEST(libc_strfmt);

    Y_UTEST(system_error);	
    Y_UTEST(system_exception);
    Y_UTEST(system_pid);

    Y_UTEST(calculus_integer_log2);
    Y_UTEST(calculus_base2);

    Y_UTEST(type_ints);

    Y_UTEST(memory_small_chunk);

}
Y_UTEST_EXEC()




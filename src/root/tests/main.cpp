#include "y/utest/driver.hpp"


Y_UTEST_DECL(8)
{
    Y_UTEST(exception);
    Y_UTEST(xml);

    Y_UTEST(config_platform);
    Y_UTEST(config_compiler);


    Y_UTEST(core_display);
    Y_UTEST(core_hsort);
    Y_UTEST(core_hindx);
    Y_UTEST(core_rand);
    Y_UTEST(core_pool);
    Y_UTEST(core_list);
    Y_UTEST(core_pool_and_list);

    Y_UTEST(libc_sort);
    Y_UTEST(libc_strfmt);

    Y_UTEST(system_error);	
    Y_UTEST(system_exception);
    Y_UTEST(system_pid);
    Y_UTEST(system_wall_time);

    Y_UTEST(calculus_integer_log2);
    Y_UTEST(calculus_base2);
    Y_UTEST(calculus_meta2);
    Y_UTEST(calculus_align);
    Y_UTEST(calculus_gc);

    Y_UTEST(type_ints);

    Y_UTEST(concurrent_nucleus);
    Y_UTEST(concurrent_ram);
    Y_UTEST(concurrent_mutex);
    Y_UTEST(concurrent_thread);
    Y_UTEST(concurrent_memory);
    Y_UTEST(concurrent_life_time);


    Y_UTEST(memory_small_chunk);
    Y_UTEST(memory_small_arena);
    Y_UTEST(memory_small_house);
    Y_UTEST(memory_small_blocks);
    Y_UTEST(memory_pages);
    Y_UTEST(memory_book);
    Y_UTEST(memory_moniker);
    Y_UTEST(memory_plastic_bricks);
    Y_UTEST(memory_plastic_forge);
    Y_UTEST(memory_auto_built);
    Y_UTEST(memory_allocator);

    Y_UTEST(pointer_auto);
}
Y_UTEST_EXEC()




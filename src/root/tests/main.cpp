#include "y/utest/driver.hpp"


Y_UTEST_DECL(8)
{
    Y_UTEST(exception);
    Y_UTEST(xml);
    Y_UTEST(object);
    Y_UTEST(light_object);

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
    Y_UTEST(calculus_required);
    Y_UTEST(calculus_split);
    Y_UTEST(calculus_isqrt);

    Y_UTEST(type_ints);

    Y_UTEST(concurrent_nucleus);
    Y_UTEST(concurrent_ram);
    Y_UTEST(concurrent_mutex);
    Y_UTEST(concurrent_thread);
    Y_UTEST(concurrent_threaded);
    Y_UTEST(concurrent_memory);
    Y_UTEST(concurrent_life_time);
    Y_UTEST(concurrent_fake_lock);
    Y_UTEST(concurrent_condition);
    Y_UTEST(concurrent_member);


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
    Y_UTEST(memory_archon);
    Y_UTEST(memory_troop);
    Y_UTEST(memory_supply);




    Y_UTEST(pointer_auto);

    Y_UTEST(ascii_base64);

    Y_UTEST(threading_gmt);
    Y_UTEST(threading_stc);
    Y_UTEST(threading_mth);
    Y_UTEST(threading_mto);

    Y_UTEST(string_stride);
    Y_UTEST(string);

    Y_UTEST(container_iter);

    Y_UTEST(apex_k);
    Y_UTEST(apex_k_bits);
    Y_UTEST(apex_n64);
}
Y_UTEST_EXEC()




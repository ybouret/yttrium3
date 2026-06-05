#include "y/utest/driver.hpp"


Y_UTEST_DECL(8)
{
    Y_UTEST(exception);
    Y_UTEST(xml);
    Y_UTEST(object);
    Y_UTEST(light_object);
    Y_UTEST(functor);

    Y_UTEST(config_platform);
    Y_UTEST(config_compiler);


    Y_UTEST(core_display);
    Y_UTEST(core_hsort);
    Y_UTEST(core_hindx);
    Y_UTEST(core_rand);
    Y_UTEST(core_pool);
    Y_UTEST(core_list);
    Y_UTEST(core_pool_and_list);
    Y_UTEST(core_tree);
    Y_UTEST(core_htable);

    Y_UTEST(libc_sort);
    Y_UTEST(libc_strfmt);
    Y_UTEST(libc_ifile);
    Y_UTEST(libc_ofile);

    Y_UTEST(system_error);	
    Y_UTEST(system_exception);
    Y_UTEST(system_pid);
    Y_UTEST(system_wall_time);
    Y_UTEST(system_hw);

    Y_UTEST(calculus_integer_log2);
    Y_UTEST(calculus_base2);
    Y_UTEST(calculus_meta2);
    Y_UTEST(calculus_align);
    Y_UTEST(calculus_gc);
    Y_UTEST(calculus_required);
    Y_UTEST(calculus_nzbits);
    Y_UTEST(calculus_split);
    Y_UTEST(calculus_isqrt);
    Y_UTEST(calculus_ldiv);
    Y_UTEST(calculus_gcd);
    Y_UTEST(calculus_primes);


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
    Y_UTEST(concurrent_split1d);
    Y_UTEST(concurrent_split2d);
    Y_UTEST(concurrent_simd);


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
    Y_UTEST(memory_buffer);


    Y_UTEST(pointer_auto);
    Y_UTEST(pointer_easy);

    Y_UTEST(ascii_base64);
    Y_UTEST(ascii_conv_u64);
    Y_UTEST(ascii_conv_i64);
    Y_UTEST(ascii_conv_apn);
    Y_UTEST(ascii_conv_apz);
    Y_UTEST(ascii_conv_flt);
    Y_UTEST(ascii_convert);


    Y_UTEST(threading_gmt);
    Y_UTEST(threading_stc);
    Y_UTEST(threading_mth);
    Y_UTEST(threading_mto);

    Y_UTEST(string_stride);
    Y_UTEST(string);
    Y_UTEST(string_in_threads);
    Y_UTEST(string_format);

    Y_UTEST(container_iter);
    Y_UTEST(container_contiguous_ro);
    Y_UTEST(container_contiguous_rw);
    Y_UTEST(container_cxx_array);
    Y_UTEST(container_cxx_series);
    Y_UTEST(container_vector);
    Y_UTEST(container_list);
    Y_UTEST(container_matrix);
    Y_UTEST(container_suffix_set);
    Y_UTEST(container_suffix_map);
    Y_UTEST(container_hash_set);
    Y_UTEST(container_hash_map);
    Y_UTEST(container_pq);
    Y_UTEST(container_lexicon);
    Y_UTEST(container_book);


    Y_UTEST(apex_k);
    Y_UTEST(apex_k_bits);
    Y_UTEST(apex_k_sd);
    Y_UTEST(apex_k_gcd);
    Y_UTEST(apex_k_dft_mul);
    Y_UTEST(apex_k_dft_sqr);
    Y_UTEST(apex_n64);
    Y_UTEST(apex_n);
    Y_UTEST(apex_n_red);
    Y_UTEST(apex_z);
    Y_UTEST(apex_q);
    Y_UTEST(apex_in_threads);
    Y_UTEST(apex_rsa);
    Y_UTEST(apex_perf);
    Y_UTEST(apex_perf2);
    Y_UTEST(apex_frontier);
    Y_UTEST(apex_overseer);

    Y_UTEST(stream_u64);
    Y_UTEST(stream_output_file);
    Y_UTEST(stream_input_file);
    Y_UTEST(stream_io64);
    Y_UTEST(stream_serialize);
    Y_UTEST(stream_gz_in);
    Y_UTEST(stream_gz_out);
    Y_UTEST(stream_identifiers);
    Y_UTEST(stream_input_proc);

    Y_UTEST(coven_univocal);
    Y_UTEST(coven_vector);
    Y_UTEST(coven_vcache);
    Y_UTEST(coven_family);
    Y_UTEST(coven_colinear);
    Y_UTEST(coven_tribes);
    Y_UTEST(coven_inquiry);
    Y_UTEST(coven_compress);

    Y_UTEST(counting_perm);
    Y_UTEST(counting_comb);
    Y_UTEST(counting_part);

    Y_UTEST(handy_caches);
    Y_UTEST(handy_lists);
    Y_UTEST(handy_basic_light_list);
    Y_UTEST(handy_basic_heavy_list);
    Y_UTEST(handy_plain_light_list);
    Y_UTEST(handy_plain_heavy_list);
    Y_UTEST(handy_joint_light_list);
    Y_UTEST(handy_joint_heavy_list);
    Y_UTEST(handy_joint_set);

    Y_UTEST(dft_mul);

    Y_UTEST(jive_source);
    Y_UTEST(jive_leading);
    Y_UTEST(jive_pattern);
    Y_UTEST(jive_posix);
    Y_UTEST(jive_rx);
    Y_UTEST(jive_scanner);
    Y_UTEST(jive_lexer);
    Y_UTEST(jive_vfs);
    Y_UTEST(jive_xnode);
    Y_UTEST(jive_grammar);

    Y_UTEST(graphviz);

    Y_UTEST(vfs_scan);

    Y_UTEST(hashing_tests);
    Y_UTEST(hashing_key_dumper);
    Y_UTEST(hashing_scatter);

    Y_UTEST(mkl_numeric);
    Y_UTEST(mkl_api);

    Y_UTEST(cameo_static_geqz_sum);
    Y_UTEST(cameo_sum_direct);
    Y_UTEST(cameo_sum_raised);
    Y_UTEST(cameo_sum_queued);
    Y_UTEST(cameo_sum_static_queued);
    Y_UTEST(cameo_sum_scalar);
    Y_UTEST(cameo_sum_vectorial);
    Y_UTEST(cameo_addition);
    Y_UTEST(cameo_product_direct);
    Y_UTEST(cameo_product_raised);
    Y_UTEST(cameo_product_queued);
    Y_UTEST(cameo_multiplication);
    Y_UTEST(cameo_addenda);
    Y_UTEST(cameo_sum3);

    Y_UTEST(info_bwt);

    Y_UTEST(random_type_gen);

    Y_UTEST(field_layouts);
    Y_UTEST(field_1d);
    Y_UTEST(field_2d);
    Y_UTEST(field_3d);
    Y_UTEST(field_4d);
}
Y_UTEST_EXEC()




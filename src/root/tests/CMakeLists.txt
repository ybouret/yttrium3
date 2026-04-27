Y_CreateTest(root
config
libc
core
system
calculus
type
concurrent
memory
memory/small
memory/plastic
pointer
ascii
threading
string
container
apex
stream
coven
counting
)

Y_LinkLibraries(test-root)

enable_testing()

Y_UTEST(exception)
Y_UTEST(xml)
Y_UTEST(object)
Y_UTEST(light_object)

Y_UTEST(config:platform)
Y_UTEST(config:compiler)

Y_UTEST(core:display)
Y_UTEST(core:hsort)
Y_UTEST(core:hindx)
Y_UTEST(core:rand)
Y_UTEST(core:pool)
Y_UTEST(core:list)
Y_UTEST(core:pool_and_list)

Y_UTEST(libc:sort)
Y_UTEST(libc:strfmt)
Y_UTEST(libc:ifile)
Y_UTEST(libc:ofile)

Y_UTEST(system:error)
Y_UTEST(system:exception)
Y_UTEST(system:pid)
Y_UTEST(system:wall_time)
Y_UTEST(system:hw)

Y_UTEST(calculus:integer_log2)
Y_UTEST(calculus:base2)
Y_UTEST(calculus:meta2)
Y_UTEST(calculus:align)
Y_UTEST(calculus:gc)
Y_UTEST(calculus:required)
Y_UTEST(calculus:split)
Y_UTEST(calculus:isqrt)
Y_UTEST(calculus:ldiv)
Y_UTEST(calculus:gcd)
Y_UTEST(calculus:primes)



Y_UTEST(type_ints)

Y_UTEST(concurrent:nucleus)
Y_UTEST(concurrent:ram)
Y_UTEST(concurrent:mutex)
Y_UTEST(concurrent:thread)
Y_UTEST(concurrent:threaded)
Y_UTEST(concurrent:memory)
Y_UTEST(concurrent:life_time)
Y_UTEST(concurrent:fake_lock)
Y_UTEST(concurrent:condition)
Y_UTEST(concurrent:member)
Y_UTEST(concurrent:split1d)
Y_UTEST(concurrent:split2d)
Y_UTEST(concurrent:simd)

Y_UTEST(memory:small:chunk)
Y_UTEST(memory:small:arena)
Y_UTEST(memory:small:house)
Y_UTEST(memory:small:blocks)
Y_UTEST(memory:pages)
Y_UTEST(memory:book)
Y_UTEST(memory:moniker)
Y_UTEST(memory:plastic:bricks)
Y_UTEST(memory:plastic:forge)
Y_UTEST(memory:auto_built)
Y_UTEST(memory:allocator)
Y_UTEST(memory:archon)
Y_UTEST(memory:troop)
Y_UTEST(memory:supply)
Y_UTEST(memory:buffer)


Y_UTEST(pointer:auto)

Y_UTEST(ascii:base64)
Y_UTEST(ascii:conv:u64)
Y_UTEST(ascii:conv:i64)
Y_UTEST(ascii:conv:apn)
Y_UTEST(ascii:conv:apz)
Y_UTEST(ascii:conv:flt)
Y_UTEST(ascii:convert)

Y_UTEST(threading:gmt)
Y_UTEST(threading:stc)
Y_UTEST(threading:mth)
Y_UTEST(threading:mto)

Y_UTEST(string:stride)
Y_UTEST(string)
Y_UTEST(string:in_threads)
Y_UTEST(string:format)

Y_UTEST(container:iter)
Y_UTEST(container:contiguous:ro)
Y_UTEST(container:contiguous:rw)
Y_UTEST(container:cxx:array)
Y_UTEST(container:cxx:series)
Y_UTEST(container:vector)
Y_UTEST(container:list)
Y_UTEST(container:matrix)

Y_UTEST(apex:k)
Y_UTEST(apex:k:bits)
Y_UTEST(apex:k:sd)
Y_UTEST(apex:k:gcd)
Y_UTEST(apex:n64)
Y_UTEST(apex:n)
Y_UTEST(apex:n:red)
Y_UTEST(apex:z)
Y_UTEST(apex:q)
Y_UTEST(apex:in_threads)
Y_UTEST(apex:rsa)

Y_UTEST(stream:u64)
Y_UTEST(stream:output:file)
Y_UTEST(stream:input:file)
Y_UTEST(stream:io64)

Y_UTEST(coven:univocal)
Y_UTEST(coven:vector)
Y_UTEST(coven:vcache)
Y_UTEST(coven:family)
Y_UTEST(coven:colinear)

Y_UTEST(counting:perm)
Y_UTEST(counting:comb)
Y_UTEST(counting:part)


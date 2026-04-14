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

Y_UTEST(system:error)
Y_UTEST(system:exception)
Y_UTEST(system:pid)
Y_UTEST(system:wall_time)

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

Y_UTEST(threading:gmt)
Y_UTEST(threading:stc)
Y_UTEST(threading:mth)
Y_UTEST(threading:mto)

Y_UTEST(string:stride)
Y_UTEST(string)

Y_UTEST(container:iter)

Y_UTEST(apex:k)
Y_UTEST(apex:k:bits)
Y_UTEST(apex:ksd)
Y_UTEST(apex:n64)
Y_UTEST(apex:n)




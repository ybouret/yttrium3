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
handy
dft
jive
vfs
hashing
mkl
cameo
info
random
)

Y_LinkLibraries(test-root)
target_link_libraries(test-root zlibstatic)

enable_testing()

Y_UTEST(exception)
Y_UTEST(xml)
Y_UTEST(object)
Y_UTEST(light_object)
Y_UTEST(functor)

Y_UTEST(config:platform)
Y_UTEST(config:compiler)

Y_UTEST(core:display)
Y_UTEST(core:hsort)
Y_UTEST(core:hindx)
Y_UTEST(core:rand)
Y_UTEST(core:pool)
Y_UTEST(core:list)
Y_UTEST(core:pool_and_list)
Y_UTEST(core:tree)
Y_UTEST(core:htable)

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
Y_UTEST(calculus:nzbits)
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
Y_UTEST(pointer:easy)

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
Y_UTEST(container:suffix:set)
Y_UTEST(container:suffix:map)
Y_UTEST(container:hash:set)
Y_UTEST(container:hash:map)
Y_UTEST(container:pq)
Y_UTEST(container:lexicon)

Y_UTEST(apex:k)
Y_UTEST(apex:k:bits)
Y_UTEST(apex:k:sd)
Y_UTEST(apex:k:gcd)
Y_UTEST(apex:k:dft:mul)
Y_UTEST(apex:k:dft:sqr)
Y_UTEST(apex:n64)
Y_UTEST(apex:n)
Y_UTEST(apex:n:red)
Y_UTEST(apex:z)
Y_UTEST(apex:q)
Y_UTEST(apex:in_threads)
Y_UTEST(apex:rsa)
Y_UTEST(apex:perf)
Y_UTEST(apex:perf2)
Y_UTEST(apex:scatter)


Y_UTEST(stream:u64)
Y_UTEST(stream:output:file)
Y_UTEST(stream:input:file)
Y_UTEST(stream:io64)
Y_UTEST(stream:serialize)
Y_UTEST(stream:gz:in)
Y_UTEST(stream:gz:out)
Y_UTEST(stream:identifiers)
Y_UTEST(stream:input:proc)

Y_UTEST(coven:univocal)
Y_UTEST(coven:vector)
Y_UTEST(coven:vcache)
Y_UTEST(coven:family)
Y_UTEST(coven:colinear)
Y_UTEST(coven:tribes)
Y_UTEST(coven:inquiry)
Y_UTEST(coven:compress)

Y_UTEST(counting:perm)
Y_UTEST(counting:comb)
Y_UTEST(counting:part)

Y_UTEST(handy:caches)
Y_UTEST(handy:lists)
Y_UTEST(handy:basic:light:list)
Y_UTEST(handy:basic:heavy:list)
Y_UTEST(handy:plain:light:list)
Y_UTEST(handy:plain:heavy:list)
Y_UTEST(handy:joint:light:list)
Y_UTEST(handy:joint:heavy:list)
Y_UTEST(handy:joint:set)

Y_UTEST(dft:mul)

Y_UTEST(jive:source)
Y_UTEST(jive:leading)
Y_UTEST(jive:pattern)
Y_UTEST(jive:posix)
Y_UTEST(jive:rx)
Y_UTEST(jive:scanner)
Y_UTEST(jive:lexer)

Y_UTEST(graphviz)

Y_UTEST(vfs:scan)

Y_UTEST(hashing:tests)
Y_UTEST(hashing:key:dumper)

Y_UTEST(mkl:numeric)
Y_UTEST(mkl:api)

Y_UTEST(cameo:static_geqz_sum)
Y_UTEST(cameo:sum:direct)
Y_UTEST(cameo:sum:raised)
Y_UTEST(cameo:sum:queued)
Y_UTEST(cameo:sum:static_queued)
Y_UTEST(cameo:sum:scalar)
Y_UTEST(cameo:sum:vectorial)
Y_UTEST(cameo:addition)
Y_UTEST(cameo:product:direct)
Y_UTEST(cameo:product:raised)
Y_UTEST(cameo:product:queued)
Y_UTEST(cameo:multiplication)
Y_UTEST(cameo:addenda)
Y_UTEST(cameo:sum3)

Y_UTEST(info:bwt)

Y_UTEST(random:type_gen)

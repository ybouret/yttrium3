
template <>
Quadratic<real_t>:: Quadratic() :
code( new Code() )
{
}

template <>
Quadratic<real_t>:: ~Quadratic() noexcept
{
    Destroy(code);
}





template <>
void Quadratic<real_t>:: step(XML::Log                & xml,
                              Triplet<real_t>         & x,
                              Triplet<real_t>         & f,
                              Function<real_t,real_t> & F)
{
    assert(code);
    return code->step(xml,x,f,F);
}


template <>
real_t Quadratic<real_t>:: find(XML::Log                & xml,
                                Triplet<real_t>         & x,
                                Triplet<real_t>         & f,
                                Function<real_t,real_t> & F,
                                const size_t              cycles)
{
    assert(code);
    return code->find(xml,x,f,F,cycles);
}

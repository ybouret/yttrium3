
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


template <>
MinTrack<real_t>:: MinTrack() : code( new Code() )
{
}

template <>
inline MinTrack<real_t>:: ~MinTrack() noexcept
{
    assert(code);
    Destroy(code);
}

template <>
real_t MinTrack<real_t>:: step(Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{
    assert(code);
    return code->step(x,f,F);
}

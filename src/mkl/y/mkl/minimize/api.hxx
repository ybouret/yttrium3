 

template <>
Minimizer<real_t>:: Minimizer() :
code( new Code() ),
verbose(code->verbose)
{
}

template <>
Minimizer<real_t>:: ~Minimizer() noexcept
{
    Destroy(code);
}

template <>
real_t Minimizer<real_t>:: find(Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{
    assert(code);
    return code->find(x,f,F);
}


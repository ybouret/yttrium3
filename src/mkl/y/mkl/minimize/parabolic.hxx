template <>
Parabolic<real_t>:: Parabolic() : code( new Code() )
{
}

template <>
Parabolic<real_t>:: ~Parabolic() noexcept
{
    Destroy(code);
}





template <>
void Parabolic<real_t>:: step(Triplet<real_t>         &x,
                              Triplet<real_t>         &f,
                              Function<real_t,real_t> &F)
{
    assert(code);
    code->step(x,f,F);
}

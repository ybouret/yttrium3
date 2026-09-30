
//__________________________________________________________________________
//
//
// Extract new triplet with AT LEAST FOUR exact numeric minima
//
//__________________________________________________________________________
inline void loadFZN(Triplet<T>    & x,
                    Triplet<T>    & f,
                    const size_t    org,
                    const size_t    len) noexcept
{
    assert(len>=4);
    const size_t nt = len-3; // number of triplets

    size_t small = org;
    size_t lower = org;
    size_t upper = org+2;
    T      width = Max(xx[upper]-xx[lower],zero);
    for(size_t t=1;t<nt;++t)
    {
        const T wtmp = Max(xx[++upper]-xx[++lower],zero);
        if(wtmp<width)
        {
            width = wtmp;
            small = lower;
        }
    }

    x.load(xx+small);
    f.load(ff+small);
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

}

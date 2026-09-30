
//
//
// Extract new triplet with ONE exact numeric minimum
//
inline void loadFZ1(Triplet<T>    & x,
                    Triplet<T>    & f,
                    const size_t         im) noexcept
{
    assert(nn>=3);
    if(0==im)
    {
        //
        // stuck on left : squeeze
        //
        x.a = x.b = xx[0];
        f.a = f.b = ff[0];
        x.c = xx[1];
        f.c = ff[1];
        assert(x.isIncreasing());
        assert(f.isLocalMinimum());
    }
    else
    {
        const size_t upper = nn-1;
        if(upper==im)
        {
            //
            // stuck on right : squeeze
            //
            const size_t lower=upper-1;
            x.a = xx[lower]; f.a = ff[lower];
            x.b = x.c = xx[upper];
            f.b = f.c = ff[upper];
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        else
        {
            //
            // core : extract
            //
            const size_t j = im-1;
            x.load(xx+j);
            f.load(ff+j);
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
    }
}

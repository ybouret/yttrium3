
//------------------------------------------------------------------------------
//
//
//! Load triplet with only one numeric minimum
//
//
//------------------------------------------------------------------------------
inline void loadFlatV1(Triplet<T>    &x,
                       Triplet<T>    &f,
                       size_t         im) noexcept
{
    if(0==im)
    {
        // at left
        x.a = x.b = xx[0];
        f.a = f.b = ff[0];
        x.c = xx[1];
        f.c = ff[1];
        assert(x.isIncreasing());
        assert(f.isLocalMinimum());
    }
    else
    {
        if(nn-1==im)
        {
            // at right
            x.b = x.c = xx[im];
            f.b = f.c = ff[im];
            --im;
            x.a  = xx[im];
            f.a = ff[im];
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        else
        {
            // in core
            --im;
            x.load(&xx[im]);
            f.load(&ff[im]);
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
    }
}



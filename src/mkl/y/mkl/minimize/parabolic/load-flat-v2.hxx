
//------------------------------------------------------------------------------
//
//
//! Load triplet with only two numeric minima: take closest point
//
//
//------------------------------------------------------------------------------
inline void loadFlatV2(Triplet<T>    &x,
                       Triplet<T>    &f,
                       size_t         lower) noexcept
{
    typedef V2D<T> v2d;
    assert(lower<nn-1);

    if(0==lower)
    {
        // at left: no choice
        x.load(xx);
        f.load(ff);
        assert(x.isIncreasing());
        assert(f.isLocalMinimum());
    }
    else
    {
        if(nn-2==lower)
        {
            // at right: no choice
            --lower;
            x.load(&xx[lower]);
            f.load(&ff[lower]);
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        else
        {
            // in core: take closest
            const size_t il    = lower-1; assert(lower>0);
            const size_t upper = lower+1;
            const size_t ir    = upper+1; assert(ir<nn);
            const v2d    vl(xx[lower]-xx[il],ff[il]-ff[lower]);
            const v2d    vr(xx[ir]-xx[upper],ff[ir]-ff[upper]);
            const T      dl = vl.mod2();
            const T      dr = vr.mod2();
            if(dl<=dr)
            {
                // with left point
                x.load(&xx[il]);
                f.load(&ff[il]);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
            else
            {
                // with right point
                x.load(&xx[lower]);
                f.load(&ff[lower]);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
        }
    }


    }

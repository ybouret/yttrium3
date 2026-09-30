
//__________________________________________________________________________
//
//
// Extract new triplet with TWO exact numeric minima
//
//__________________________________________________________________________
inline void loadFZ2(Triplet<T>    & x,
                    Triplet<T>    & f,
                    const size_t    org) noexcept
{
    assert(nn>=3);

    if(org<=0)
    {
        //------------------------------------------------------------------
        //
        // take left-most triplet
        //
        //------------------------------------------------------------------
        x.load(xx);
        f.load(ff);
        assert(x.isIncreasing());
        assert(f.isLocalMinimum());
    }
    else
    {
        const size_t top = nn-3;
        if(org>=top)
        {
            //--------------------------------------------------------------
            //
            // take right-most triplet
            //
            //--------------------------------------------------------------
            x.load(xx+top);
            f.load(ff+top);
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        else
        {
            //--------------------------------------------------------------
            //
            // got at least one point at each side: take closest
            //
            //--------------------------------------------------------------
            assert(org>0);
            assert(org<top);
            const size_t lo = org-1;
            const size_t up = org+3; assert(up<nn);
            const T      dl = Max(xx[org]-xx[lo],  zero);
            const T      dr = Max(xx[up]-xx[up-1], zero);
            if(dl<=dr)
            {
                // take left point
                x.load(xx+lo);
                f.load(ff+lo);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
            else
            {
                // take right point
                x.load(xx+org);
                f.load(ff+org);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
        }
    }
}

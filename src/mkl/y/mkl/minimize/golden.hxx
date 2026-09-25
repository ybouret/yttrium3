
namespace
{


    static inline
    void GoldenLoadFZ1(Triplet<real_t>    & x,
                       Triplet<real_t>    & f,
                       const real_t * const xx,
                       const real_t * const ff,
                       const size_t         nn,
                       const size_t         im) noexcept
    {
        assert(nn>=4);
        if(0==im)
        {
            // stuck on left
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
                // stuck on right
                const size_t lower=upper-1;
                x.a = xx[lower]; f.a = ff[lower];
                x.b = x.c = xx[upper];
                f.b = f.c = ff[upper];
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
            else
            {
                // core
                const size_t j = im-1;
                x.load(xx+j);
                f.load(ff+j);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
        }
    }

    static inline
    void GoldenLoadFZ2(Triplet<real_t>    & x,
                       Triplet<real_t>    & f,
                       const real_t * const xx,
                       const real_t * const ff,
                       const size_t         nn,
                       const size_t         org) noexcept
    {
        assert(nn>=4);

        if(org<=0)
        {
            // take left-most triplet
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
                // take right-most triplet
                x.load(xx+top);
                f.load(ff+top);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            }
            else
            {
                assert(org>0);
                assert(org<top);
                const size_t lo = org-1;
                const size_t up = org+3; assert(up<nn);
                const real_t dl = Max(xx[org]-xx[lo],  Numeric<real_t>::ZERO);
                const real_t dr = Max(xx[up]-xx[up-1], Numeric<real_t>::ZERO);
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

    static inline
    void GoldenLoadFZN(Triplet<real_t>    & x,
                       Triplet<real_t>    & f,
                       const real_t * const xx,
                       const real_t * const ff,
                       const size_t         org,
                       const size_t         len) noexcept
    {
        assert(len>=4);
        const size_t nt = len-3; // number of triplets
        std::cerr << "nt=" << nt << std::endl;

        size_t small = org;
        size_t lower = org;
        size_t upper = org+2;
        real_t width = Max(xx[upper]-xx[lower],  Numeric<real_t>::ZERO);
        for(size_t t=1;t<nt;++t)
        {
            const real_t wtmp = Max(xx[++upper]-xx[++lower],  Numeric<real_t>::ZERO);
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




    static inline
    void GoldenExtract(Triplet<real_t>    & x,
                       Triplet<real_t>    & f,
                       const real_t * const xx,
                       const real_t * const ff,
                       const size_t         nn) noexcept
    {
        assert(nn>=4);

#if !defined(NDEBUG)
        for(size_t i=1;i<nn;++i) {
            assert(xx[i-1]<=xx[i]);
        }

#endif // !defined(NDEBUG)

        //----------------------------------------------------------------------
        //
        //
        // Locate imin
        //
        //
        //----------------------------------------------------------------------
        size_t imin = 0;
        real_t fmin = ff[0];
        for(size_t i=1;i<nn;++i)
        {
            const real_t ftmp = ff[i];
            if(ftmp<fmin)
            {
                imin = i;
                fmin = ftmp;
            }
        }


        //----------------------------------------------------------------------
        //
        //
        // Locate left flat zone
        //
        //
        //----------------------------------------------------------------------
        size_t nl = 0;
        {
            const size_t nlMax = imin;
            for(size_t i=1;i<=nlMax;++i)
            {
                if(ff[imin-i]>fmin) break;
                nl = i;
            }
        }

        //----------------------------------------------------------------------
        //
        //
        // Locate right flat zone
        //
        //
        //----------------------------------------------------------------------
        size_t nr = 0;
        {
            const size_t nrMax = nn-imin;
            for(size_t i=1;i<=nrMax;++i)
            {
                if(ff[imin+i]>fmin) break;
                nr = i;
            }
        }

        //----------------------------------------------------------------------
        //
        //
        // Compute flat zone
        //
        //
        //----------------------------------------------------------------------
        const size_t flatZone = 1 + nl + nr;

        switch( flatZone )
        {

            case 1:
                GoldenLoadFZ1(x,f,xx,ff,nn,imin);
                break;

            case 2:
                assert(imin>=nl);
                GoldenLoadFZ2(x,f,xx,ff,nn,imin-nl);
                break;

            case 3: {
                assert(imin>=nl);
                const size_t org = imin - nl;
                x.load(xx+org);
                f.load(ff+org);
                assert(x.isIncreasing());
                assert(f.isLocalMinimum());
            } break;

            default:
                assert(flatZone>=4);
                GoldenLoadFZN(x,f,xx,ff,imin-nl,flatZone);
        }

    }
}

template <>
void Golden<real_t>:: Step(XML::Log &xml, Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{
    Y_XML_Element(xml,GoldenStep);

    //--------------------------------------------------------------------------
    //
    //
    // prepare increasing x
    //
    //
    //--------------------------------------------------------------------------
    assert(x.isOrdered());
    assert(f.isLocalMinimum());
    if(x.a>x.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
        assert(x.isIncreasing());
        assert(f.isLocalMinimum());
    }

    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

    Y_XMLog(xml,"--  x=" << x << ", f=" << f);

    if(false)
    {
        OutputFile fp("golden-step.dat");
        GoldenSaveState(fp,x,f,2);
    }

    static const size_t NMAX = 8;
    real_t xx[NMAX];
    real_t ff[NMAX];

    {
        Y_BZero(xx);
        Y_BZero(ff);
        size_t       nn = 0;
        const real_t ab = Max(x.b-x.a,Numeric<real_t>::ZERO);
        const real_t bc = Max(x.c-x.b,Numeric<real_t>::ZERO);

        switch( Sign::Of(ab,bc) )
        {
            case Negative:
                assert(bc>ab); // cut bc
                ff[0] = f.a; xx[0] = x.a;
                ff[1] = f.b; xx[1] = x.b;
                ff[2] =   F( xx[2] = Clamp(x.b,x.b + Numeric<real_t>::GOLDEN_C * bc,x.c) );
                ff[3] = f.c; xx[3] = x.c;
                nn    = 4;
                break;

            case Positive:
                assert(ab>bc); // cut ab
                ff[0] = f.a; xx[0] = x.a;
                ff[1] =   F( xx[1] = Clamp(x.a,x.b - Numeric<real_t>::GOLDEN_C * ab,x.b) );
                ff[2] = f.b; xx[2] = x.b;
                ff[3] = f.c; xx[3] = x.c;
                nn    = 4;
                break;

            case __Zero__:   // cut both
                ff[0] = f.a; xx[0] = x.a;
                ff[1] =   F( xx[1] = Clamp(x.a,x.b - Numeric<real_t>::GOLDEN_C * ab,x.b) );
                ff[2] = f.b; xx[2] = x.b;
                ff[3] =   F( xx[3] = Clamp(x.b,x.b + Numeric<real_t>::GOLDEN_C * bc,x.c) );
                ff[4] = f.c; xx[4] = x.c;
                nn    = 5;
                break;
        }

        GoldenExtract(x,f,xx,ff,nn);
        Y_XMLog(xml,"--> x=" << x << ", f=" << f);

    }



    if(false)
    {
        OutputFile fp("golden-step.dat",true);
        GoldenSaveState(fp,x,f,3);
    }

}


template <>
real_t Golden<real_t>:: Find(XML::Log &xml, Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{
    Y_XML_Element(xml,GoldenFind);
    assert(x.isOrdered());
    assert(f.isLocalMinimum());

    // initialize search
    Step(xml,x,f,F);
    real_t xopt = x.b;

    size_t step=0;
    size_t flat=0;

    // process
STEP:
    ++step;
    Y_XMLog(xml,"step #" << step);
    Step(xml,x,f,F);
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());
    if( AlmostEqual<real_t>::Are(f.a,f.b) && AlmostEqual<real_t>::Are(f.b,f.c))
    {
        if(flat<=0) flat = step;
        Y_XMLog(xml, "[f-cvg @step #" << flat << "]");

        if( AlmostEqual<real_t>::Are(xopt,x.b))
        {
            Y_XMLog(xml, "[x-cvg @step #" << step << "]");
            goto DONE;
        }
    }

    xopt = x.b;
    goto STEP;

DONE:
    f.b = F(x.b);
    return x.b;


}


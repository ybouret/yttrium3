


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

    Y_XMLog(xml,"x=" << x << ", f=" << f);

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

            case __Zero__: // cut both
                ff[0] = f.a; xx[0] = x.a;
                ff[1] =   F( xx[1] = Clamp(x.a,x.b - Numeric<real_t>::GOLDEN_C * ab,x.b) );
                ff[2] = f.b; xx[2] = x.b;
                ff[3] =   F( xx[3] = Clamp(x.b,x.b + Numeric<real_t>::GOLDEN_C * bc,x.c) );
                ff[4] = f.c; xx[4] = x.c;
                nn    = 5;
                break;
        }

    }


#if 0
    //--------------------------------------------------------------------------
    //
    //
    // check intervals
    //
    //
    //--------------------------------------------------------------------------
    const real_t ab = Max(x.b-x.a,Numeric<real_t>::ZERO);
    const real_t bc = Max(x.c-x.b,Numeric<real_t>::ZERO);

    if(ab>bc)
    {
        //----------------------------------------------------------------------
        //
        // cut ab
        //
        //----------------------------------------------------------------------
        const real_t x_g = Clamp(x.a,x.b - Numeric<real_t>::GOLDEN_C * ab,x.b);
        const real_t f_g = F(x_g);
        const bool   ok  = f_g < f.b;
        if(ok)
        {
            // new min
            x.c = x.b; f.c = f.b;
            x.b = x_g; f.b = f_g;
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        else
        {
            // .b remains, .a moves
            x.a = x_g; f.a = f_g;
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        Y_XMLog(xml,"[>]" << (ok?"[+]":"[-]") << " F(" << x_g << ") = " << f_g);

    }
    else
    {
        //----------------------------------------------------------------------
        //
        // cut bc
        //
        //----------------------------------------------------------------------
        const real_t x_g = Clamp(x.b,x.b + Numeric<real_t>::GOLDEN_C * bc,x.c);
        const real_t f_g = F(x_g);
        const bool   ok  = f_g < f.b;
        if(ok)
        {
            // new min
            x.a = x.b; f.a = f.b;
            x.b = x_g; f.b = f_g;
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        else
        {
            // .b remains, .c moves
            x.c = x_g; f.c = f_g;
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
        }
        Y_XMLog(xml,"[<]" << (ok?"[+]":"[-]") << " F(" << x_g << ") = " << f_g);
    }

    Y_XMLog(xml,"x=" << x << ", f=" << f);
#endif

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

    size_t cycle = 0;
    size_t iflat = 0;
STEP:
    ++cycle;
    Y_XMLog(xml,"cycle #" << cycle);
    Step(xml,x,f,F);
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());
    if( AlmostEqual<real_t>::Are(f.a,f.b) && AlmostEqual<real_t>::Are(f.b,f.c))
    {
        if(!iflat) iflat = cycle;
        Y_XMLog(xml, "[flat region @" << iflat << "]");
    }

    if( AlmostEqual<real_t>::Are(x.a,x.c) )
    {
        Y_XMLog(xml, "[pinpoint]");
        abort();
    }

    goto STEP;

    f.b = F(x.b);
    return x.b;
}


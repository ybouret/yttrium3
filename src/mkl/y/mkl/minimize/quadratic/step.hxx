inline void step(XML::Log      &xml,
                 Triplet<T>    &x,
                 Triplet<T>    &f,
                 Function<T,T> &F)
{

    //--------------------------------------------------------------------------
    //
    //
    // initialize with local minimum, assuming ordered x
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

    if(Trace)
    {
        {
            const unsigned np  = 100;
            OutputFile fp("quad-data.dat");
            fp("%.15g %.15g\n", (double)x.a, (double)f.a);
            for(unsigned i=1;i<np;++i)
            {
                const T xt = x.a + ( (T) i ) * (x.c-x.a) / (T)np;
                const T ft = F(xt);
                fp("%.15g %.15g\n", (double)xt, (double)ft);
            }
            fp("%.15g %.15g\n", (double)x.c, (double)f.c);
        }

        {
            OutputFile fp("quad-inp.dat");
            Save(fp, &x[1], &f[1], 3);
        }
    }

    //--------------------------------------------------------------------------
    //
    //
    // perform step
    //
    //
    //--------------------------------------------------------------------------
    Y_XML_Element_Attr(xml,QuadraticStep,Y_XML_Attr(x) << Y_XML_Attr(f));
    extrapolate(xml,x,f,F);
    goldenRatio(xml,x,f,F);

}


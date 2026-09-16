


template <>
void Golden<real_t>:: Step(XML::Log &xml, Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{
    assert(x.isOrdered());
    assert(f.isLocalMinimum());

    Y_XML_Element(xml,GoldenStep);
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
    {
        OutputFile fp("golden-step.dat");
        GoldenSaveState(fp,x,f,2);
    }

    const real_t ab = Max(x.b-x.a,Numeric<real_t>::ZERO);
    const real_t bc = Max(x.c-x.b,Numeric<real_t>::ZERO);

    if(ab>bc)
    {
        // cut ab
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
        // cut bc
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

    {
        OutputFile fp("golden-step.dat",true);
        GoldenSaveState(fp,x,f,3);
    }

}

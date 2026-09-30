
inline void extrapolate(XML::Log      &xml,
                        Triplet<T>    &x,
                        Triplet<T>    &f,
                        Function<T,T> &F)
{
    Y_XML_Element_Attr(xml,Extrapolate,Y_XML_Attr(x) << Y_XML_Attr(f));
    clear();

    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

    //--------------------------------------------------------------------------
    //
    //
    // unfold cases
    //
    //
    //--------------------------------------------------------------------------
    if(x.b<=x.a)
    {
        //----------------------------------------------------------------------
        //
        // beta <= 0
        //
        //----------------------------------------------------------------------
        Y_XMLog(xml, "[<]");
        sample(xml,x.b,f.b);
        sample(xml,Clamp(x.b,x.b + Numeric<T>::GOLDEN_C * (x.c-x.b), x.c),F);
        sample(xml,x.c,f.c);
        assert(3==nn);
    }
    else
    {
        if(x.b>=x.c)
        {
            //------------------------------------------------------------------
            //
            // beta >= 1
            //
            //------------------------------------------------------------------
            Y_XMLog(xml, "[>]");
            sample(xml,x.a,f.a);
            sample(xml,Clamp(x.a,x.b-Numeric<T>::GOLDEN_C * (x.b-x.a), x.b),F);
            sample(xml,x.b,f.b);
            assert(3==nn);
        }
        else
        {
            //------------------------------------------------------------------
            //
            // generic case
            //
            //------------------------------------------------------------------
            Y_XMLog(xml, "[*]");
            sample(xml,x.a,f.a);
            sample(xml,x.b,f.b);
            sample(xml,x.c,f.c);
            assert(3==nn);
            const T alpha = f.a - f.b; assert(alpha>=zero);
            const T gamma = f.c - f.b; assert(gamma>=zero);

            if( AlmostEqual<T>::Are(alpha,gamma) )
            {
                //--------------------------------------------------------------
                //
                // symmetrical
                //
                //--------------------------------------------------------------
                Y_XMLog(xml, "[=]");
                sample(xml,Half<T>(x.a,x.c),F);
            }
            else
            {
                //--------------------------------------------------------------
                //
                // generic
                //
                //--------------------------------------------------------------
                Y_XMLog(xml, "[#]");
                const T width = x.c-x.a; assert(width>zero);
                const T beta  = Clamp(zero, (x.b-x.a)/(x.c-x.a), one);
                const T omb   = one - beta;
                const T den   = beta * gamma + omb * alpha;
                const T sigma = f.c - f.a;
                vmul.set(beta);
                vmul.mul(omb);
                vmul.mul(sigma);
                const T twice = one - vmul()/den;
                const T uquad = Half<T>(twice);
                sample(xml,Clamp(x.a,x.a+uquad*width,x.c),F);
            }

        }
    }

    extract(xml,x,f);

}

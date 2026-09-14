
//______________________________________________________________________________
//
//
//! best effort to add point(s) towards parabolic approximation
//
//______________________________________________________________________________

inline void grow(XML::Log      & xml,
                 Triplet<T>    & x,
                 Triplet<T>    & f,
                 FunctionType  & F)
{
    Y_XML_Element_Attr(xml,Grow,Y_XML_Attr(x) << Y_XML_Attr(f));
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

    const T width = x.c-x.a;
    if(x.b<=x.a)
    {
        //----------------------------------------------------------
        //
        //
        // beta=0
        //
        //
        //----------------------------------------------------------
        Y_XMLog(xml, "[beta<=0]");
        sample(xml,Clamp(x.a,x.a+C*width,x.c),F); // golden from left side
    }
    else
    {
        if(x.b>=x.c)
        {
            //------------------------------------------------------
            //
            //
            // beta=1
            //
            //
            //------------------------------------------------------
            Y_XMLog(xml, "[beta>=1]");
            sample(xml,Clamp(x.a,x.c-C*width,x.c),F); // golden from right side
        }
        else
        {
            //------------------------------------------------------
            //
            //
            // 0<beta<1
            //
            //
            //------------------------------------------------------
            const T        beta  = Clamp(zero,(x.b-x.a)/width,one);
            const T        omb   = Clamp(zero,one-beta,one);
            const T        alpha = f.a-f.b;
            const T        gamma = f.c-f.b;

            switch(Sign::Of(alpha,gamma))
            {
                case __Zero__:
                    Y_XMLog(xml, "[alpha=gamma]" );
                    sample(xml,Clamp(x.a,x.a+half*width,x.c),F); // middle
                    break;

                case Negative: {
                    assert(alpha<gamma);
                    Y_XMLog(xml, "[alpha<gamma]" );
                    const T eta = alpha/gamma;
                    const T u_m = Clamp(zero,half*(one-beta*omb*(one-eta)/(beta+omb*eta)),one);
                    sample(xml,Clamp(x.a,x.a+u_m*(x.c-x.a),x.c),F); // towards x.a
                } break;

                case Positive: {
                    Y_XMLog(xml, "[alpha>gamma]");
                    const T eta = gamma/alpha;
                    const T u_m = Clamp(zero,half*(one + beta*omb*(one-eta)/(beta*eta+omb)),one);
                    sample(xml,Clamp(x.a,x.a+u_m*(x.c-x.a),x.c),F); // towads x.c
                } break;


            }
        }
    }


    // extract new state
    extract(xml,x,f);
}

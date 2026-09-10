
template <>
bool Bracket::Inside<real_t>( XML::Log &xml, Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{

    Y_XML_Element(xml,BracketInside);

    //--------------------------------------------------------------------------
    //
    // ensure .a is the minimum
    //
    //--------------------------------------------------------------------------
    if(f.a>f.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }
    assert(f.a<=f.c);

    bool result = false;
    while(true)
    {
        //----------------------------------------------------------------------
        //
        // move using golden ration
        //
        //----------------------------------------------------------------------
        x.b = Secure(x.a,x.a + Numeric<real_t>::GOLDEN_C * (x.c -x.a),x.c); assert(x.isOrdered());
        f.b = F(x.b);
        Y_XMLog(xml, "x=" << x << "; f=" << f << " #" << Sign::HumanReadable( x.getSign()) );

        //----------------------------------------------------------------------
        //
        // check for strict (?) local minimum
        //
        //----------------------------------------------------------------------
        if( f.b < f.a )
        {
            assert(f.b<f.c);
            assert(f.isLocalMinimum());
            Y_XMLog(xml, "[success] local minimum" );
            result = true;
            break;
        }

        //----------------------------------------------------------------------
        //
        // check for global minimum
        //
        //----------------------------------------------------------------------
        if( AlmostEqual<real_t>::Are(x.a,x.b) || AlmostEqual<real_t>::Are(x.b,x.c) )
        {
            x.b = x.c = x.a;
            f.b = f.c = f.a;
            Y_XMLog(xml, "[failure] global minimum" );
            break;
        }
        
        //----------------------------------------------------------------------
        //
        // move triplet
        //
        //----------------------------------------------------------------------
        f.c = f.b;
        x.c = x.b;
    }

    return result;
}

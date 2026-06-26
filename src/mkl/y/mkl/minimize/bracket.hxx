
template <>
bool Bracket::Inside<real_t>( XML::Log &xml, Triplet<real_t> &x, Triplet<real_t> &f, Function<real_t,real_t> &F)
{

    Y_XML_Element(xml,BracketInside);

    // ensure a is the minimum
    if(f.a>f.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }
    assert(f.a<=f.c);
    Y_XMLog(xml, "F(" << x.a << ")=" << f.a << " => F(" << x.c << ")=" << f.c);


    // loop
    while(true)
    {
        assert(f.a<=f.c);

        f.b = F( x.b = Clamp(x.a,Half<real_t>::Of(x.a,x.c),x.c) );
        Y_XMLog(xml, "F(" << x.b << ")=" << f.b);
        if(f.b<=f.a)
        {
            assert(f.b<=f.c);
            assert(f.isLocalMinimum());
            Y_XMLog(xml, "[success] local minimum" );
            return true;
        }

        f.c = f.b;
        x.c = x.b;

        if( AlmostEqual<real_t>::Are(x.a,x.b))
        {
            x.b = x.c = x.a;
            f.b = f.c = f.a;
            Y_XMLog(xml, "[failure] global minimum" );
            return false;
        }
    }


    return true;
}

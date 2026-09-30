
inline void goldenRatio(XML::Log &xml, Triplet<T> &x, Triplet<T> &f, Function<T,T> &F)
{
    Y_XML_Element(xml,GoldenRatio);
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

    //--------------------------------------------------------------------------
    //
    //
    // Initialize
    //
    //
    //--------------------------------------------------------------------------
    clear();
    x.save(xx),
    f.save(ff);
    nn=3;

    //--------------------------------------------------------------------------
    //
    //
    // check which side to cut
    //
    //
    //--------------------------------------------------------------------------
    const T ab = Max<T>(x.b-x.a,zero);
    const T bc = Max<T>(x.c-x.b,zero);
    Y_XMLog(xml,"left=" << ab << " | right=" << bc);
    switch( Sign::Of(ab,bc) )
    {
        case Negative: assert(ab<bc);
            // cut bc
            Y_XMLog(xml, "[<]");
            sample(xml,Clamp(x.b, x.b + bc * C, x.c),F);
            break;

        case Positive: assert(ab>bc);
            // cut ab
            Y_XMLog(xml, "[>]");
            sample(xml,Clamp(x.a, x.b - ab * C, x.b),F);
            break;

        case __Zero__:
            // cut both
            Y_XMLog(xml, "[><]");
            sample(xml,Clamp(x.b, x.b + bc * C, x.c),F);
            sample(xml,Clamp(x.a, x.b - ab * C, x.b),F);
            break;
    }

    extract(xml,x,f);

}

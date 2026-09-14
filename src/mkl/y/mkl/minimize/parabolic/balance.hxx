
inline void sampleRight(XML::Log      & xml,
                        const T         rw,
                        Triplet<T>    & x,
                        Function<T,T> & F)
{
    sample(xml, Clamp(x.b,x.b + C*rw, x.c), F);
}

inline void sampleLeft(XML::Log      & xml,
                       const T         lw,
                       Triplet<T>    & x,
                       Function<T,T> & F)
{
    sample(xml, Clamp(x.a,x.b - C*lw, x.b), F);
}


inline void balance(XML::Log      & xml,
                    Triplet<T>    & x,
                    Triplet<T>    & f,
                    Function<T,T> & F)
{
    Y_XML_Element(xml,Balance);
    assert(x.isOrdered());
    assert(f.isLocalMinimum());

    //--------------------------------------------------------------------------
    //
    // initialize length
    //
    //--------------------------------------------------------------------------
    T lw   = Max(x.b-x.a,zero);
    T rw   = Max(x.c-x.b,zero);
    while(true)
    {
        //----------------------------------------------------------------------
        //
        // load current state
        //
        //----------------------------------------------------------------------
        preload(x,f);

        //----------------------------------------------------------------------
        //
        // Reduce largest segment, or both
        //
        //----------------------------------------------------------------------
        switch( Sign::Of(lw,rw) )
        {
            case Negative: assert(lw<rw);           sampleRight(xml,rw,x,F); break;
            case Positive: assert(lw>rw);           sampleLeft(xml,lw,x,F);  break;
            case __Zero__: sampleRight(xml,rw,x,F); sampleLeft(xml,lw,x,F);  break;
        }

        //----------------------------------------------------------------------
        //
        // extract new state
        //
        //----------------------------------------------------------------------
        extract(xml,x,f);

        //----------------------------------------------------------------------
        //
        // update lengths and check balance
        //
        //----------------------------------------------------------------------
        T  wmin = (lw = Max(x.b-x.a,zero));
        T  wmax = (rw = Max(x.c-x.b,zero));
        if(wmin>wmax) Swap(wmin,wmax);

        assert(wmin<=wmax);
        Y_XMLog(xml,"-- wmin=" << wmin << ", wmax=" << wmax);
        if(wmax<=wmin+wmin)
            break;
    }


}

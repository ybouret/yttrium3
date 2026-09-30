inline T find(XML::Log      &xml,
              Triplet<T>    &x,
              Triplet<T>    &f,
              Function<T,T> &F,
              const size_t   cycles)
{
    Y_XML_Element(xml,QuadraticFind);

    //--------------------------------------------------------------------------
    //
    //
    // initialize
    //
    //
    //--------------------------------------------------------------------------
    const bool debug = cycles>0; // user's choice
    size_t     count = 0;        // cycles
    size_t     iflat = 0;        // flatness index

    //--------------------------------------------------------------------------
    //
    //
    // loop
    //
    //
    //--------------------------------------------------------------------------
    {
        T xopt = x.b;
        while(true)
        {
            ++count;
            step(xml,x,f,F);

            const T xnew = x.b;

            if( AlmostEqual<T>::Are(f.a,f.b) && AlmostEqual<T>::Are(f.b,f.c) )
            {
                if(iflat<=0) iflat = count;
                Y_XMLog(xml, "[flat from #" << iflat << "]");
                if( AlmostEqual<T>::Are(xnew,xopt) )
                {
                    Y_XMLog(xml, "[converged @" << count << "]");
                    break;
                }
            }

            xopt = xnew;
            if( debug&& (count>=cycles) )
            {
                Y_XMLog(xml, "[debugging break!]");
                break;
            }
        }
    }

    //--------------------------------------------------------------------------
    //
    //
    // finalize
    //
    //
    //--------------------------------------------------------------------------
    f.b = F(x.b);
    return x.b;
}

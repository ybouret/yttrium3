#include "load-flat-v1.hxx"
#include "load-flat-v2.hxx"
#include "load-flat-vn.hxx"

inline void extract(XML::Log      &xml,
                    Triplet<T>    &x,
                    Triplet<T>    &f)
{
    Y_XML_Element_Attr(xml, Extract, Y_XML_Attr(nn) );

    //--------------------------------------------------------------------------
    //
    // order xx and ff to have local representation
    //
    //--------------------------------------------------------------------------
    Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);
    if(xml.verbose)
    {
        Core::Display( xml() << "xx=",xx,nn) << std::endl;
        Core::Display( xml() << "ff=",ff,nn) << std::endl;
    }

    //--------------------------------------------------------------------------
    //
    // find numeric minimum interval
    //
    //--------------------------------------------------------------------------
    size_t imin=0;
    size_t same=1;
    T      fmin = ff[0];
    for(size_t i=1;i<nn;++i)
    {
        const T ftmp = ff[i];
        switch( Sign::Of(ftmp,fmin) )
        {
            case Negative: imin = i; fmin=ftmp; same=1; continue;
            case Positive: break;
            case __Zero__: ++same; continue;
        }
        break;
    }

    Y_XMLog(xml,"fmin=" << fmin << " #" << same);

    //--------------------------------------------------------------------------
    //
    // process according to interval length
    //
    //--------------------------------------------------------------------------
    switch(same)
    {
        case 0: throw Specific::Exception("Parabolic::Step", "Corrupted");
        case 1: loadFlatV1(x,f,imin); break;
        case 2: loadFlatV2(x,f,imin); break;
        case 3: x.load(&xx[imin]); f.load(&ff[imin]);        break;
        default: assert(same>=4); loadFlatVN(x,f,imin,same); break;
    }

    Y_XMLog(xml, "--> x=" << x << "; f=" << f);
}

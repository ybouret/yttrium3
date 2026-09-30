
#include "fz1.hxx"
#include "fz2.hxx"
#include "fzn.hxx"

inline void extract(XML::Log   & xml,
                    Triplet<T> & x,
                    Triplet<T> & f)
{
    Y_XML_Element_Attr(xml,Extract, Y_XML_Attr(nn));
    Core::HSort::Make(xx,nn,Sign::Increasing<T>,ff);


#if !defined(NDEBUG)
    for(size_t i=1;i<nn;++i)
        assert(xx[i-1]<=xx[i]);
#endif


    // locate a minimum value
    size_t imin = 0;
    T      fmin = ff[0];
    for(size_t i=1;i<nn;++i)
    {
        const T ftmp = ff[i];
        if(ftmp<fmin)
        {
            imin = i;
            fmin = ftmp;
        }
    }


    // Locate left flat zone
    size_t nl = 0;
    {
        const size_t nlMax = imin;
        for(size_t i=1;i<=nlMax;++i)
        {
            if(ff[imin-i]>fmin) break;
            nl = i;
        }
    }


    // Locate right flat zone
    size_t nr = 0;
    {
        const size_t nrMax = nn-imin;
        for(size_t i=1;i<nrMax;++i)
        {
            if(ff[imin+i]>fmin) break;
            nr = i;
        }
    }


    // Compute flat zone
    const size_t flatZone = 1 + nl + nr;
    //std::cerr << "flatZone = 1+" << nl << "+" << nr << " = " << flatZone << " @" << imin << std::endl;
    assert(flatZone<=nn);

    switch(flatZone)
    {
        case 0: throw Specific::Exception("Quadratic::Extract", "corrupted!");
        case 1: loadFZ1(x,f,imin);
            break;

        case 2: loadFZ2(x,f,imin-nl);
            break;

        case 3: {
            const size_t org = imin-nl;
            x.load(xx+org);
            f.load(ff+org);
        } break;

        default:
            loadFZN(x,f,imin-nl,flatZone);
    }
    
}

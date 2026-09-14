
//------------------------------------------------------------------------------
//
//
//! Load triplet with at least 4 numeric minima: smallest interval
//
//
//------------------------------------------------------------------------------
inline void loadFlatVN(Triplet<T>    &x,
                       Triplet<T>    &f,
                       const size_t   imin,
                       const size_t   same) noexcept
{
    assert(same>=4);
    assert(nn>=4);
    const size_t nt = same-2;          // number of triplets
    size_t       im = imin;            // initial index
    T            wm = xx[im+2]-xx[im]; // initial width

    for(size_t j=1,i=imin+1;j<nt;++j,++i)
    {
        const T w = xx[i+2]-xx[i];
        if(w<wm) {
            im = i;
            wm = w;
        }
    }
    
    x.load(&xx[im]); assert(x.isOrdered());
    f.load(&ff[im]); assert(f.isLocalMinimum());
}

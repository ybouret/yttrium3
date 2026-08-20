//______________________________________________________________________________
//
//
// Multiplication
//
//______________________________________________________________________________

//! compute irow-th term of matrix/vector multiplication
/**
 \param irow 1<=irow<=rows
 \param xadd inner addition
 \param source compatible source
 \return dot(row[irow],source)
 */
template <typename U, typename SOURCE> inline
U mul_(const size_t         irow,
       Cameo::Addition<U> & xadd,
       SOURCE &             source) const
{
    assert(cols==source.size());
    assert(irow<=rows);
    assert(irow>0);
    return xadd.dot( row[irow], source);
}

//! in place multiplication: target = *this * source \param target output vector \param source input vector
template <typename TARGET, typename SOURCE> inline
void mul(TARGET &target, SOURCE &source) const
{
    assert(rows==target.size());
    assert(cols==source.size());
    Cameo::Addition<T> xadd(cols);
    for(size_t i=rows;i>0;--i)
        target[i] = mul_(i,xadd,source);
}

//______________________________________________________________________________
//
//
// Multiplication/Addition
//
//______________________________________________________________________________

//! compute irow-th term of matrix/vector multiplication with addition
/**
 \param irow   1<=irow<=rows
 \param xadd   inner addition
 \param source compatible source
 \param rhs    vector to add
 \return dotadd(row[irow],source,rhs[irow])
 */
template <typename U, typename SOURCE, typename RHS> inline
U muladd_(const size_t         irow,
          Cameo::Addition<U> & xadd,
          SOURCE &             source,
          RHS &                rhs ) const
{
    assert(cols==source.size());
    assert(irow<=rows);
    assert(irow>0);
    return xadd.dotadd( row[irow], source, rhs[irow]);
}

//! in place multiplication and addition : target = *this * source + rhs
/**
 \param target output vector
 \param source input vector
 \param rhs    vector to add
 */
template <typename TARGET, typename SOURCE, typename RHS> inline
void muladd(TARGET &target, SOURCE &source, RHS &rhs) const
{
    assert(rows==target.size());
    assert(cols==source.size());
    assert(rows==rhs.size());
    Cameo::Addition<T> xadd(cols);
    for(size_t i=rows;i>0;--i)
        target[i] = muladd_(i,xadd,source,rhs);
}

//______________________________________________________________________________
//
//
// Multiplication/Subtraction
//
//______________________________________________________________________________

//! compute irow-th term of matrix/vector multiplication with subtraction
/**
 \param irow   1<=irow<=rows
 \param xadd   inner addition
 \param source compatible source
 \param rhs    vector to sub
 \return dotadd(row[irow],source,rhs[irow])
 */
template <typename U, typename SOURCE, typename RHS> inline
U mulsub_(const size_t         irow,
          Cameo::Addition<U> & xadd,
          SOURCE &             source,
          RHS &                rhs ) const
{
    assert(cols==source.size());
    assert(irow<=rows);
    assert(irow>0);
    return xadd.dotsub( row[irow], source, rhs[irow]);
}

//! in place multiplication and subtraction : target = *this * source - rhs
/**
 \param target output vector
 \param source input vector
 \param rhs    vector to subtract
 */
template <typename TARGET, typename SOURCE, typename RHS> inline
void mulsub(TARGET &target, SOURCE &source, RHS &rhs) const
{
    assert(rows==target.size());
    assert(cols==source.size());
    assert(rows==rhs.size());
    Cameo::Addition<T> xadd(cols);
    for(size_t i=rows;i>0;--i)
        target[i] = mulsub_(i,xadd,source,rhs);
}

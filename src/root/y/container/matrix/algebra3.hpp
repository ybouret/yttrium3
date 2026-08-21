
template <typename LHS, typename RHS> inline
T mmul_(LHS                &lhs,
        RHS                &rhs,
        Cameo::Addition<T> &xadd,
        const size_t        i,
        const size_t        j)
{
    assert(lhs.rows==rows);
    assert(rhs.cols==cols);
    assert(lhs.cols==rhs.rows);
    const size_t nx   = lhs.cols;
    xadd.ldz();
    for(size_t k=nx;k>0;--k)
        xadd.addProd(lhs[i][k], rhs[k][j]);
    return xadd();
}

//! *this = lhs * rhs \param lhs matrix \param rhs matrix
template <typename LHS, typename RHS> inline
void mmul(LHS &lhs, RHS &rhs)
{
    assert(lhs.rows==rows);
    assert(rhs.cols==cols);
    assert(lhs.cols==rhs.rows);
    Matrix &           self = *this;
    const size_t       nr   = rows;
    const size_t       nc   = cols;
    const size_t       nx   = lhs.cols;
    Cameo::Addition<T> xadd(nx);
#if 0
    for(size_t i=nr;i>0;--i)
    {
        for(size_t j=nc;j>0;--j)
        {
            xadd.ldz();
            for(size_t k=nx;k>0;--k)
                xadd.addProd(lhs[i][k], rhs[k][j]);
            self[i][j] = xadd();

        }
    }
#endif
    for(size_t i=nr;i>0;--i)
        for(size_t j=nc;j>0;--j)
            self[i][j] = mmul_(lhs,rhs,xadd,i,j);
}


//! *this = lhs * rhs' \param lhs matrix \param rhs matrix
template <typename LHS, typename RHS> inline
void mmul(LHS &lhs, const TransposeOf_ &, RHS &rhs)
{
    assert(rows==lhs.rows);
    assert(cols==rhs.rows);
    assert(lhs.cols==rhs.cols);
    Matrix &           self = *this;
    const size_t       nr   = rows;
    const size_t       nc   = cols;
    Cameo::Addition<T> xadd(lhs.cols);
    for(size_t i=nr;i>0;--i)
    {
        for(size_t j=nc;j>0;--j)
            self[i][j] = xadd.dot(lhs[i],rhs[j]);
    }
}

//! *this = lhs' * rhs \param lhs matrix \param rhs matrix
template <typename LHS, typename RHS> inline
void mmul(const TransposeOf_ &, LHS &lhs, RHS &rhs)
{
    assert(rows==lhs.cols);
    assert(cols==rhs.cols);
    assert(lhs.rows==rhs.rows);
    Matrix &           self = *this;
    const size_t       nr   = rows;
    const size_t       nc   = cols;
    const size_t       nx   = lhs.rows;
    Cameo::Addition<T> xadd(nx);
    for(size_t i=nr;i>0;--i)
    {
        for(size_t j=nc;j>0;--j)
        {
            xadd.ldz();
            for(size_t k=nx;k>0;--k)
                xadd.addProd(lhs[k][i],rhs[k][j]);
            self[i][j] = xadd();
        }
    }
}

//! compute Gram matrix \param P to compute P'*P
template <typename MATRIX> inline
void gram(MATRIX &P)
{
    assert(P.rows==rows);
    assert(P.rows==cols);
    Matrix &           self = *this;
    const size_t       nr   = rows;
    Cameo::Addition<T> xadd(P.cols);
    for(size_t i=1;i<=nr;++i)
    {
        self[i][i] = xadd.dot(P[i],P[i]);
        for(size_t j=i+1;j<=nr;++j)
            self[i][j] = self[j][i] = xadd.dot(P[i],P[j]);
    }
}

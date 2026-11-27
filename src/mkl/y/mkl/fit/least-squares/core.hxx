
template <>
LeastSquaresCore<real_t>:: ~LeastSquaresCore() noexcept {}

template <>
void LeastSquaresCore<real_t>::  buildLambda() noexcept
{
    const real_t ten = 10;
    Coerce(lambda[0]) = 1;
    for(unit_t i=-1;i>PMIN;--i) Coerce(lambda[i]) = lambda[i+1]/ten;
    for(unit_t i=1;i<=PMAX;++i) Coerce(lambda[i]) = lambda[i-1]*ten;
}

template <>
LeastSquaresCore<real_t>:: LeastSquaresCore() :
beta(),
alpha(),
curv(),
lu(),
step(),
aini(),
aend(),
atmp(),
lambda( LambdaName, Field::Layout1D(PMIN,PMAX) ),
zero(0),
one(1)
{
    buildLambda();
}

template <>
void LeastSquaresCore<real_t>::  prepareCoreFor(const size_t nvar)
{
    //----------------------------------------------------------
    // prepare beta
    //----------------------------------------------------------
    beta.adjust(nvar);
    beta.ld(zero);

    //----------------------------------------------------------
    // prepare alpha and curv
    //----------------------------------------------------------
    alpha.make(nvar,nvar);
    alpha.ld(zero).diag(one);
    curv.make(nvar,nvar);

    //----------------------------------------------------------
    // prepare other
    //----------------------------------------------------------
    step.adjust(nvar);
    aini.adjust(nvar);
    aend.adjust(nvar);
    atmp.adjust(nvar);

    //----------------------------------------------------------
    // prepare inner additions
    //----------------------------------------------------------
    this->readyFor(nvar);
}

template <>
void LeastSquaresCore<real_t>:: compileFrom(const Variables      &vars,
                                           const Readable<bool> &used)
{
    Variables::ConstIterator it = vars->begin();
    for(size_t i=vars->size();i>0;--i,++it)
    {
        const Variable &v_i = **it;if(!v_i[used]) continue;
        AdditionType   &sum = *v_i[sumBeta];
        v_i[beta] = sum();

        MatrixRow<AdditionHandle> & sa_i = v_i[sumAlpha];
        MatrixRow<real_t>         & a_i  = v_i[alpha];
        Variables::ConstIterator    jt   = it;
        for(size_t j=i;j>0;--j,++jt)
        {
            const Variable & v_j  = **jt; if(!v_j[used]) continue;
            AdditionType   & sum  = *v_j[sa_i];
            const real_t     a_ij = sum();
            v_j[a_i]        = a_ij;
            v_i[v_j[alpha]] = a_ij;
        }

    }
}

template <>
CurvatureResult LeastSquaresCore<real_t>:: buildCurvature(unit_t &p)
{
    assert(p>=PMIN);
    assert(p<=PMAX);
    size_t         cycle = 1; SCALE:
    const real_t   scale = one + lambda[p];
    curv.assign(alpha);
    for(size_t i=curv.rows;i>0;--i)
        curv[i][i] *= scale;


    if( lu.build(curv) )
        return (1 == cycle) ? Straight : Expanded;

    if(++p>PMAX) return Singular;
    ++cycle;
    goto SCALE;
}


template <>
bool LeastSquaresCore<real_t>:: converged() const noexcept
{
    for(size_t i=aini.size();i>0;--i)
    {
        if( !AlmostEqual<real_t>::Are(aini[i],aend[i])) return false;
    }
    return true;
}

template <>
bool LeastSquaresCore<real_t>:: Increase(unit_t &p) noexcept
{
    if(++p>PMAX)
        return false;
    else
        return true;
}

template<>
void LeastSquaresCore<real_t>:: Decrease(unit_t &p) noexcept
{
    InSituMax(--p,PMIN);
}

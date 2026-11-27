
template <>
Probe<real_t>:: ~Probe() noexcept {}

template <>
Probe<real_t>:: Probe() : sumD2(), sumBeta(), sumAlpha(), addenda()
{
}

template <>
void Probe<real_t>:: readyFor(const size_t nvar)
{
    //--------------------------------------------------------------------------
    // adjust memory
    //--------------------------------------------------------------------------
    assert(nvar>0);
    sumBeta.adjust(nvar);
    sumAlpha.make(nvar,nvar);
    AdditionType * node = addenda.make( (nvar*(nvar+3)) >> 1 );

    //--------------------------------------------------------------------------
    // fill sumBeta with nvar nodes
    //--------------------------------------------------------------------------
    for(size_t i=1;i<=nvar;++i,node=node->next)
    {
        assert(node);
        sumBeta[i] = node;
    }

    //--------------------------------------------------------------------------
    // fill sumAlpha with nvar*(1+nvar)/2 symetric nodes
    //--------------------------------------------------------------------------
    for(size_t i=1;i<=nvar;++i)
    {
        for(size_t j=i;j<=nvar;++j,node=node->next)
        {
            assert(node);
            sumAlpha[i][j] = sumAlpha[j][i] = node;
        }
    }

    sumD2.ldz();
    addenda.ldz();
}

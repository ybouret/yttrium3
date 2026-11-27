inline void step(SampleType               & S,
                 unit_t                   & p,
                 FunctionType             & F,
                 GradientType             & G,
                 Writable<ABSCISSA>       & aorg,
                 const Readable<bool>     & used)
{

    //--------------------------------------------------------------------------
    //
    //
    // Link temporary context
    //
    //
    //--------------------------------------------------------------------------
    const Temporary<FunctionType*> tmpF(myF,&F);
    const Temporary<SampleType*>   tmpS(myS,&S);



    //--------------------------------------------------------------------------
    //
    //
    // Build full metrics
    //
    //
    //--------------------------------------------------------------------------
    Triplet<ABSCISSA>  D  = { D2full(S,G,aorg,used),-1,-1 };
    std::cerr << "D2_org=" << D.a << std::endl;

    //--------------------------------------------------------------------------
    //
    //
    // Build local curvature
    //
    //
    //--------------------------------------------------------------------------
    const CurvatureResult topo   = this->buildCurvature(p);
    if(Singular == topo )
    {

        return;
    }

    //--------------------------------------------------------------------------
    //
    //
    // Build step from/into beta
    //
    //
    //--------------------------------------------------------------------------
    std::cerr << "beta=" << beta << std::endl;
    this->lu.solve(curv,beta);

    std::cerr << "step=" << beta << std::endl;

    S.vars.transfer(aini.ld(zero),aorg);

    std::cerr << "aorg=" << aorg << " => aini=" << aini << std::endl;
    const size_t n = aini.size();
    for(size_t i=n;i>0;--i)
    {
        aend[i] = aini[i] + beta[i];
    }

    // TODO: clip with intervals ?

    //--------------------------------------------------------------------------
    //
    //
    // evaluate trial step
    //
    //
    //--------------------------------------------------------------------------
    D.c = D2(S,F,aend);
    std::cerr << "D2_try=" << D.c << std::endl;

    {
        OutputFile fp("d2.txt");
        for(double u=0;u<1.0;u += 0.01)
        {
            fp("%g %g\n", u, (double) (*this)(u));
        }
    }

    //--------------------------------------------------------------------------
    //
    //
    // check result
    //
    //
    //--------------------------------------------------------------------------
    if(D.c<D.a)
    {
        //----------------------------------------------------------------------
        //
        // Improved D2
        //
        //----------------------------------------------------------------------
        
    }
    else
    {
        //----------------------------------------------------------------------
        //
        // Worsen D2
        //
        //----------------------------------------------------------------------
    }

}


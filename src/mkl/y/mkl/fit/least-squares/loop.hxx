inline void loop(XML::Log                 & xml,
                 SampleType               & S,
                 unit_t                   & p,
                 FunctionType             & F,
                 GradientType             & G,
                 Writable<ABSCISSA>       & aorg,
                 const Readable<bool>     & used)
{

    Y_XML_Element(xml,LS_Loop);
    if(xml.verbose)
    {
        Y_XMLog(xml, "-- starting point:");
        S.vars.display(*xml,"\t(*) ",aorg,0);
    }


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
    const ABSCISSA D2_org= D2full(S,G,aorg,used);
    Y_XMLog(xml, "-- metrics:");
    Y_XMLog(xml, "D2_org = " << D2_org);
    Y_XMLog(xml, "beta   = " << beta);

    //--------------------------------------------------------------------------
    //
    //
    // Build local curvature
    //
    //
    //--------------------------------------------------------------------------
CURV:
    Y_XMLog(xml, "-- using p=" << p);
    const CurvatureResult res   = this->buildCurvature(p);
    Y_XMLog(xml, "-- curvature result was '" << CurvatureNamed::Value(res) << "'");
    if(Singular == res )
    {
        Y_XMLog(xml, "-- failure...");
        return;
    }

    //--------------------------------------------------------------------------
    //
    //
    // Build step from/into beta
    //
    //
    //--------------------------------------------------------------------------
    step.load(beta);
    this->lu.solve(curv,step);
    if(xml.verbose)
        S.vars.display(*xml,"\t[+] d_",step,0);

    S.vars.transfer(aini.ld(zero),aorg);

    const size_t n = aini.size();
    for(size_t i=n;i>0;--i)
    {
        aend[i] = aini[i] + step[i];
    }

    // TODO: clip with intervals ?
    if(xml.verbose)
    {
        Y_XMLog(xml, "-- landing point:");
        S.vars.display(*xml,"\t(*) ",aend,0);
    }



    //--------------------------------------------------------------------------
    //
    //
    // evaluate trial step
    //
    //
    //--------------------------------------------------------------------------
    const ABSCISSA D2_try = D2(S,F,aend);
    Y_XMLog(xml,"D2_try=" << D2_try);

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
    const bool cvg = this->converged();
    Y_XMLog(xml, "-- convergence: " << (cvg?"true" : "false") );

    if(D2_try<D2_org)
    {
        this->Decrease(p);


    }
    else
    {
        if(!this->Increase(p))
        {
            return;
        }

        goto CURV;
    }


}


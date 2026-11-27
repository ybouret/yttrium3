inline void operator()(XML::Log                 & xml,
                       SampleType               & S,
                       FunctionType             & F,
                       GradientType             & G,
                       Writable<ABSCISSA>       & aorg,
                       const Readable<bool>     & used)
{

    Y_XML_Element(xml,LS_Loop);
    size_t cycle = 0;
    unit_t p     = this->PMIN/2;
FULL:
    ++cycle;
    if(xml.verbose)
    {
        Y_XMLog(xml, "-- starting point for cycle #" << cycle);
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
    Y_XMLog(xml, "-- D2_org = " << D2_org);
    Y_XMLog(xml, "-- beta   = " << beta);

    //--------------------------------------------------------------------------
    //
    //
    // Build local curvature
    //
    //
    //--------------------------------------------------------------------------
    size_t sub = 0;
CURV:
    ++sub;
    Y_XMLog(xml, "-- using p=" << p << " @cycle@#" << cycle << "." << sub);
    const CurvatureResult res   = this->buildCurvature(p);
    const char * const    rid   = CurvatureNamed::Value(res);
    Y_XMLog(xml, "-- curvature result was '" << rid << "'");
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
    Y_XMLog(xml,"-- D2_try=" << D2_try);

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
    Y_XMLog(xml, "-- convergence on each variable: " << (cvg?"true" : "false") );

    if(D2_try<D2_org)
    {
        // better D2
        Y_XMLog(xml, "-- D2 decreased with " << rid << " Curvature");
        this->Decrease(p);
        S.vars.transfer(aorg,aend);
        switch(res)
        {
            case Straight:
                if(cvg)
                {
                    Y_XMLog(xml, "-- clear convergence");
                    return;
                }
                break; // => need to loop again, not converged

            case Expanded:
                if(cvg)
                    Y_XMLog(xml, "-- need to decrease bias");
                break; // => need to loop again in any case

            case Singular:
                throw Specific::Exception("LeastSquares", "corrupted code");
        }
        goto FULL;
    }
    else
    {
        // worse D2
        Y_XMLog(xml, "-- D2 increased");

        if(cvg)
        {
            Y_XMLog(xml,"-- fuzzy convergence");
            S.vars.transfer(aorg,aend);
            return;
        }

        // need to slow down step
        if(!this->Increase(p))
        {
            return;
        }

        // and try again
        goto CURV;
    }


}


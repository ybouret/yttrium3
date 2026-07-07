
#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/exception.hpp"
#include "y/mkl/root/zrid.hpp"
#include "y/core/display.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Aftermath:: ~Aftermath() noexcept
        {
        }

        Aftermath:: Aftermath(const EqStatus _st, const xreal_t _xi) noexcept :
        st(_st),
        xi(_xi)
        {
        }

        Aftermath:: Aftermath(const Aftermath &_) noexcept :
        st(_.st),
        xi(_.xi)
        {

        }



        const char * const Aftermath:: CallSign = "Aftermath";


        class Aftermath::Engine
        {
        public:
            inline Engine(XWritable        & usrC,
                          const Components & usrE,
                          const xreal_t      usrK,
                          const xreal_t      usrS,
                          const Level        usrL,
                          XMul             & usrX) noexcept :
            solve(),
            C(usrC),
            E(usrE),
            K(usrK),
            S(usrS),
            X(usrX),
            L(usrL)
            {
            }


            inline virtual ~Engine() noexcept
            {
            }

            inline xreal_t operator()(void)
            {
                return E.massAction(K,X,C,L);
            }

            inline xreal_t operator()(const real_t xi)
            {
                return E.massAction(K,X,C,L,xi);
            }

            xreal_t cycle(XML::Log &);


            MKL::ZRid<xreal_t> solve;
            XWritable        & C;
            const Components & E;
            const xreal_t      K;
            const xreal_t      S;
            XMul             & X;
            const Level        L;

        private:
            Y_Disable_Copy_And_Assign(Engine);
        };

        xreal_t Aftermath::Engine:: cycle(XML::Log &xml)
        {

            //Y_XML_Element(xml,Cycle);
            // initializing
            const xreal_t  zero(0);
            Engine        &F  = *this;
            XTriplet       xi = {  zero, zero, zero };
            XTriplet       ma = {  F(),  zero, zero };
            const SignType ms = Sign::Of(ma.a.mantissa);
            Y_XMLog(xml,"ma = " << ma.a.str());
            
            // need to find xi.c
            switch(E.kind)
            {
                case Outlawed:
                    throw Specific::Exception(CallSign,"empty '%s'", E.name.c_str());

                case ProdOnly:
                    switch(ms)
                    {
                        case __Zero__:
                            return zero;

                        case Positive:
                            xi.c = S;
                            ma.c = F(xi.c); assert(ma.c<=zero);
                            break;
                            //throw Specific::Exception(CallSign,"todo ProdOnly>0");

                        case Negative:
                            xi.c = -E.prod.extent(C,L);
                            ma.c = F(xi.c); assert(ma.c>=zero);
                            break;
                    }
                    break;

                case ReacOnly:
                    throw Specific::Exception(CallSign,"todo ReacOnly");
                    break;

                case BothWays:
                    switch(ms)
                    {
                        case __Zero__:
                            return zero;

                        case Positive:
                            xi.c = E.reac.extent(C,L);
                            ma.c = F(xi.c); assert(ma.c<=zero);
                            break;

                        case Negative:
                            xi.c = - E.prod.extent(C,L);
                            ma.c = F(xi.c); assert(ma.c>=zero);
                            break;
                    }
                    break;
            }

            const xreal_t ex = solve(F,xi,ma);
            Y_XMLog(xml,"ex = " << ex.str());
            E.safeMove(C,L,ex);
            Core::Display(std::cerr << "C=", &C[1], C.size(), xreal_t::ToString) << std::endl;

            return ex;
        }


        Aftermath Aftermath:: Compute(XML::Log         &xml,
                                      XWritable        &Cout,
                                      const Level       Lout,
                                      const XReadable  &Cinp,
                                      const Level       Linp,
                                      const Components &eq,
                                      const xreal_t     eK,
                                      XMul &            xmul,
                                      XAdd &            xadd)
        {
            const String &eid = eq.name;
            Y_XML_Element_Attr(xml,AftermathCompute,Y_XML_Attr(eid));

            //------------------------------------------------------------------
            //
            // setup
            //
            //------------------------------------------------------------------
            Cout.load(Cinp); // check
            EqStatus es = Running;

            if(eq.reac.active(Cinp,Linp) )
            {
                // active reactants
                if(eq.prod.active(Cinp,Linp))
                {
                    // active products
                    assert(Running==es);
                }
                else
                {
                    // inactive products
                    es = Crucial;
                }
            }
            else
            {
                // inactive reactants
                if(eq.prod.active(Cinp,Linp))
                {
                    // active products
                    es = Crucial;
                }
                else
                {
                    es = Blocked;
                    Y_XMLog(xml, "[Blocked]");
                    return Aftermath(es,0);
                }
            }


            assert(Running==es||Crucial==es);
            if(xml.verbose)
            {
                Core::Display( xml() << "C=", &Cout[1], Cout.size(), xreal_t::ToString) << std::endl;
                if(Crucial==es) xml() << "[Crucial]" << std::endl;
            }


            {
                xreal_t S; // scaling factor
                switch(eq.kind)
                {
                    case Outlawed:
                    case BothWays:
                        break;

                    case ProdOnly:
                        std::cerr << "d_nu=" << eq.d_nu << std::endl;
                        assert(eq.d_nu>0);

                        S = (eK+eK);
                        S = S.pow( 1.0/eq.d_nu );
                        std::cerr << "K = " << eK.str() << " => S=" << S.str() << std::endl;
                        break;

                    case ReacOnly:
                        throw Exception("Need to compute scaling for ReacOnly");
                }

                Engine  F(Cout,eq,eK,S,Lout,xmul);
                xreal_t xi = F.cycle(xml);
                xreal_t ax = MKL::Fabs<xreal_t>(xi);
                while(true)
                {
                    if( Sign::Of(xi.mantissa) == __Zero__ )
                        break;
                    const xreal_t newXi = F.cycle(xml);
                    const xreal_t absXi = MKL::Fabs<xreal_t>(newXi);
                    if(absXi>=ax) break;
                    xi = newXi;
                    ax = absXi;
                }
            }

            // need to recompute full extent
            const xreal_t xi = eq.extent(Cinp, Linp, Cout, Lout, xadd);
            Y_XMLog(xml, "xi = " << xi.str());
            return Aftermath(es,xi);
        }

    }

}



#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/exception.hpp"
#include "y/mkl/root/zrid.hpp"
#include "y/core/display.hpp"

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
                          const real_t       usrK,
                          const Level        usrL,
                          XMul             & usrX) noexcept :
            solve(),
            C(usrC),
            E(usrE),
            K(usrK),
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

            xreal_t cycle();


            MKL::ZRid<xreal_t> solve;
            XWritable        & C;
            const Components & E;
            const xreal_t      K;
            XMul             & X;
            const Level        L;

        private:
            Y_Disable_Copy_And_Assign(Engine);
        };

        xreal_t Aftermath::Engine:: cycle()
        {
            static const xreal_t zero(0);

            Engine        &F  = *this;
            XTriplet       xi = {  0,  0, 0 };
            XTriplet       ma = { F(), 0, 0 };
            const SignType ms = Sign::Of(ma.a.mantissa);
            std::cerr << "ma=" << (double)ma.a << std::endl;

            switch(E.kind)
            {
                case Outlawed:
                    throw Specific::Exception(CallSign,"empty '%s'", E.name.c_str());

                case ProdOnly:
                    throw Specific::Exception(CallSign,"todo ProdOnly");
                    break;

                case ReacOnly:
                    throw Specific::Exception(CallSign,"todo ReacOnly");
                    break;

                case BothWays:
                    switch(ms)
                    {
                        case __Zero__:
                            return 0;

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
            std::cerr << "\tex=" << (double)ex << std::endl;
            E.saveMove(C,L,ex);
            Core::Display(std::cerr << "C=", &C[1], C.size(), xreal_t::ToString) << std::endl;

            return ex;
        }


        Aftermath Aftermath:: Compute(XWritable        &Cout,
                                      const XReadable  &Cinp,
                                      const Components &eq,
                                      const xreal_t     eK,
                                      const Level       L,
                                      XMul &            xmul,
                                      XAdd &            xadd)
        {
            // setup
            Cout.load(Cinp);
            EqStatus es = Running;

            if(eq.reac.active(Cinp,L) )
            {
                // active reactants
                if(eq.prod.active(Cinp,L))
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
                if(eq.prod.active(Cinp,L))
                {
                    // active products
                    es = Crucial;
                }
                else
                {
                    es = Blocked;
                    return Aftermath(es,0);
                }
            }


            assert(Running==es||Crucial==es);
            Core::Display(std::cerr << "C=", &Cout[1], Cout.size(), xreal_t::ToString) << std::endl;
            if(Crucial==es) std::cerr << "Crucial!" << std::endl;

            {
                Engine F(Cout,eq,eK,L,xmul);
                xreal_t xi = F.cycle();
                xreal_t ax = MKL::Fabs<xreal_t>(xi);
                while(true)
                {
                    if( Sign::Of(xi.mantissa) == __Zero__ )
                        break;
                    const xreal_t newXi = F.cycle();
                    const xreal_t absXi = MKL::Fabs<xreal_t>(newXi);
                    if(absXi>=ax) break;
                    xi = newXi;
                    ax = absXi;
                }
            }

            // need to recompute full extent
            const xreal_t xi = eq.extent(Cinp, Cout, L, xadd);
            std::cerr << "xi=" << (real_t)xi << std::endl;
            return Aftermath(es,xi);
        }

    }

}


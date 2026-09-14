
#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/exception.hpp"
#include "y/mkl/api/almost-equal.hpp"
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

        Aftermath:: Aftermath(const EqStatus _st,
                              const xreal_t  _xi,
                              const size_t   _nz) noexcept :
        st(_st),
        xi(_xi),
        ax(xi.abs()),
        nz(_nz)
        {
        }

        Aftermath:: Aftermath(const Aftermath &_) noexcept :
        st(_.st),
        xi(_.xi),
        ax(_.ax),
        nz(_.nz)
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


            inline virtual ~Engine() noexcept {}

            //! mass action at initial point
            inline xreal_t operator()(void) { return E.massAction(K,X,C,L); }

            //! mass action with given extent
            inline xreal_t operator()(const real_t xi) { return E.massAction(K,X,C,L,xi); }

            //! \return new extent from current state
            xreal_t cycle();


            MKL::ZRid<xreal_t> solve;
            XWritable        & C;
            const Components & E;
            const xreal_t      K;
            const xreal_t      S;
            XMul             & X;
            const Level        L;

        private:
            Y_Disable_Copy_And_Assign(Engine);

            //! solve with sign conservation
            xreal_t solve1D(XTriplet &xi, XTriplet &ma, const SignType sa);

        };

        xreal_t Aftermath::Engine:: cycle()
        {

            //------------------------------------------------------------------
            //
            // initializing
            //
            //------------------------------------------------------------------
            const xreal_t  zero = MKL::Numeric<xreal_t>::ZERO;
            Engine        &F    = *this;
            XTriplet       x    = {  zero, zero, zero };
            XTriplet       ma   = {  F(),  zero, zero };
            const SignType ms   = Sign::Of(ma.a.mantissa);

            //------------------------------------------------------------------
            //
            // need to find x.c
            //
            //------------------------------------------------------------------
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
                            x.c  = S;
                            ma.c = F(x.c); assert(ma.c<=zero);
                            break;

                        case Negative:
                            x.c  = -E.prod.extent(C,L);
                            ma.c = F(x.c); assert(ma.c>=zero);
                            break;
                    }
                    break;

                case ReacOnly:
                    switch(ms)
                    {
                        case __Zero__:
                            return zero;

                        case Positive:
                            x.c  = E.reac.extent(C,L);
                            ma.c = F(x.c); assert(ma.c<=zero);
                            break;

                        case Negative:
                            x.c  = -S;
                            ma.c = F(x.c); assert(ma.c>=zero);
                            break;
                            //throw Specific::Exception(CallSign,"todo Negative ReacOnly");
                    }
                    break;

                case BothWays:
                    switch(ms)
                    {
                        case __Zero__:
                            return zero;

                        case Positive:
                            x.c  = E.reac.extent(C,L);
                            ma.c = F(x.c); assert(ma.c<=zero);
                            break;

                        case Negative:
                            x.c  = - E.prod.extent(C,L);
                            ma.c = F(x.c); assert(ma.c>=zero);
                            break;
                    }
                    break;
            }

            assert(__Zero__!=ms);

            // specific solver
            //const xreal_t ex = solve(F,x,ma);
            const xreal_t ex = F.solve1D(x,ma,ms);
            E.safeMove(C,L,ex);
            return ex;
        }


        xreal_t Aftermath:: Engine:: solve1D(XTriplet      & xi,
                                             XTriplet      & ma,
                                             const SignType  sa)
        {
            //------------------------------------------------------------------
            //
            // sanity check
            //
            //------------------------------------------------------------------
            assert(__Zero__!=sa);
            assert(Sign::Opposite(sa) == Sign::Of(ma.c) );

            //------------------------------------------------------------------
            //
            // select side
            //
            //------------------------------------------------------------------
            xreal_t * xn = 0, *mn=0;
            xreal_t * xp = 0, *mp=0;

            if( Negative == sa )
            {
                xn = & xi.a; mn = & ma.a;
                xp = & xi.c; mp = & ma.c;
            }
            else
            {
                assert(Positive==sa);
                xp = & xi.a; mp = & ma.a;
                xn = & xi.c; mn = & ma.c;
            }


            //------------------------------------------------------------------
            //
            // find (almost) zero
            //
            //------------------------------------------------------------------
            Engine &F = *this;
            while(true)
            {
                xi.b = xi.middle();
                ma.b = F(xi.b);

                switch(Sign::Of(ma.b))
                {
                    case __Zero__:
                        return xi.b; // just evaluated, strict zero

                    case Negative:
                        // replace negative side
                        *xn = xi.b;
                        *mn = ma.b;
                        break;

                    case Positive:
                        // replace positive side
                        *xp = xi.b;
                        *mp = ma.b;
                        break;
                }

                // check convergence
                if( MKL::AlmostEqual<xreal_t>::Are(xi.a,xi.c))
                {
                    // keep the same sign!!
                    ma.b = ma.a = F(xi.b=xi.a);
                    return xi.a;
                }
            }
        }



#define Y_CHEM_SHOW(LABEL) \
do { if(xml.verbose) eq.displayCompact( xml() << "[" #LABEL "] ",Cinp,Linp) << std::endl; } while(false)

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
            EqStatus es  = Running;
            size_t   nrz = 0;
            size_t   npz = 0;
            if(eq.reac.active(Cinp,Linp) )
            {
                //--------------------------------------------------------------
                //
                // active reactants
                //
                //--------------------------------------------------------------
                assert(eq.reac.countZeroed(Cinp,Linp)<=0);

                if(eq.prod.active(Cinp,Linp))
                {
                    //----------------------------------------------------------
                    // active products
                    //----------------------------------------------------------
                    assert(eq.prod.countZeroed(Cinp,Linp)<=0);
                    assert(Running==es);
                    Y_CHEM_SHOW(Running);
                }
                else
                {
                    //----------------------------------------------------------
                    // inactive products
                    //----------------------------------------------------------
                    npz = eq.prod.countZeroed(Cinp,Linp); assert(npz>0);
                    es  = Crucial;
                    Y_CHEM_SHOW(Crucial);
                }
            }
            else
            {
                //--------------------------------------------------------------
                //
                // inactive reactants
                //
                //--------------------------------------------------------------
                nrz = eq.reac.countZeroed(Cinp,Linp); assert(nrz>0);

                if(eq.prod.active(Cinp,Linp))
                {
                    //----------------------------------------------------------
                    // active products
                    //----------------------------------------------------------
                    assert(eq.prod.countZeroed(Cinp,Linp)<=0);
                    es = Crucial;
                    Y_CHEM_SHOW(Crucial);
                }
                else
                {
                    //----------------------------------------------------------
                    // inactive products
                    //----------------------------------------------------------
                    npz = eq.prod.countZeroed(Cinp,Linp); assert(npz>0);
                    es = Blocked;
                    Y_CHEM_SHOW(Blocked);
                    return Aftermath(es,0,nrz+npz);
                }
            }


            assert(Running==es||Crucial==es);



            {
                xreal_t S; // scaling factor
                switch(eq.kind)
                {
                    case Outlawed:
                    case BothWays:
                        break;

                    case ProdOnly:
                        //std::cerr << "d_nu=" << eq.d_nu << std::endl;
                        assert(eq.d_nu>0);
                        S = (eK+eK);
                        S = S.pow( 1.0/eq.d_nu );
                        //std::cerr << "K = " << eK.str() << " => S=" << S.str() << std::endl;
                        break;

                    case ReacOnly:
                        //std::cerr << "d_nu=" << eq.d_nu << std::endl;
                        assert(eq.d_nu<0);
                        S = 2.0/eK;
                        S = S.pow( -1.0/eq.d_nu);
                        //std::cerr << "K = " << eK.str() << " => S=" << S.str() << std::endl;
                        break;
                }

                Engine  F(Cout,eq,eK,S,Lout,xmul);
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

            //------------------------------------------------------------------
            //
            // need to recompute full extent
            //
            //------------------------------------------------------------------
            const xreal_t xi = eq.extent(Cinp, Linp, Cout, Lout, xadd);
            const size_t  nz = nrz+npz; assert( nz==eq.countZeroed(Cinp,Linp) );
            if(xml.verbose)
            {
                eq.displayCompact( xml() << "[Solving] ",Cout,Lout) << std::endl;
                xml()
                << "|_@xi = " << std::setw(24) << xi.str()
                << ", nz=" << nrz << "+" << npz << "=" << nz
                << ", (ma=" << eq.massAction(eK,xmul,Cout,Lout) << ")"
                << std::endl;
            }

            return Aftermath(es,xi,nz);
        }

    }

}


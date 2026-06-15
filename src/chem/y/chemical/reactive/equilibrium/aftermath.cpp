
#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/exception.hpp"

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

        namespace
        {
            class AMFunc
            {
            public:
                inline AMFunc(XWritable        & usrC,
                              const Components & usrE,
                              const real_t       usrK,
                              XMul             & usrX) noexcept :
                C(usrC),
                E(usrE),
                K(usrK),
                X(usrX)
                {
                }


                inline virtual ~AMFunc() noexcept
                {
                }

                XWritable        & C;
                const Components & E;
                const xreal_t      K;
                XMul             & X;

            private:
                Y_Disable_Copy_And_Assign(AMFunc);
            };
        }

        Aftermath Aftermath:: Compute(XWritable        &Cout,
                                      const XReadable  &Cinp,
                                      const Components &eq,
                                      const xreal_t     eK,
                                      XMul &            xmul)
        {
            Cout.load(Cinp);
            switch(eq.kind)
            {
                case Outlawed: throw Specific::Exception(CallSign,"empty '%s'", eq.name.c_str());
                case ProdOnly: break;
                case ReacOnly: break;
                case BothWays: break;
            }
            return Aftermath(Blocked,0);
        }
        
    }

}


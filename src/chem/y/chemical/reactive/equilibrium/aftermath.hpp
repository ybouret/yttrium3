
//! \file

#ifndef Y_Chemical_Aftermath_Included
#define Y_Chemical_Equilibrium_Format_Included 1

#include "y/chemical/reactive/components.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //! Equilibrium Status
        enum EqStatus
        {
            Blocked, //!< a zero concentration on both sides
            Running, //!< all positive concentrations
            Crucial  //!< a zero concentration on one side only
        };

        class Aftermath
        {
        public:
            static const char * const CallSign;
            class                     Engine;

            Aftermath(const EqStatus, const xreal_t) noexcept;
            Aftermath(const Aftermath &) noexcept;
            ~Aftermath() noexcept;

            static Aftermath Compute(XWritable        &Cout,
                                     const XReadable  &Cinp,
                                     const Components &eq,
                                     const xreal_t     eK,
                                     const Level       L,
                                     XMul &            xmul,
                                     XAdd &            xadd);

            const EqStatus st;
            const xreal_t  xi;
            
        private:
            Y_Disable_Assign(Aftermath);
            Aftermath OnProdOnly(XWritable &, Components &, const xreal_t, XMul &);
        };

    }

}

#endif // !Y_Chemical_Aftermath_Included


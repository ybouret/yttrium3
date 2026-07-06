
//! \file

#ifndef Y_Chemical_Aftermath_Included
#define Y_Chemical_Aftermath_Included 1

#include "y/chemical/reactive/components.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Equilibrium Status
        //
        //
        //______________________________________________________________________
        enum EqStatus
        {
            Blocked, //!< a zero concentration on both sides
            Running, //!< all positive concentrations
            Crucial  //!< a zero concentration on one side only
        };

        //______________________________________________________________________
        //
        //
        //
        //! 1D equilibrium solver
        //
        //
        //______________________________________________________________________
        class Aftermath
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Aftermath"
            class                     Engine;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Aftermath(const EqStatus, const xreal_t) noexcept; //!< setup
            Aftermath(const Aftermath &)             noexcept; //!< duplicate
            ~Aftermath()                             noexcept; //!< cleanup

            //! solve 1D equilibrium
            /**
             \param Cout solved state
             \param Cinp input state
             \param eq   components
             \param eK   constant
             \param xmul multiplication
             \param xadd addition
             \return detailed status
             */
            static Aftermath Compute(XWritable        &Cout,
                                     const XReadable  &Cinp,
                                     const Components &eq,
                                     const xreal_t     eK,
                                     const Level       L,
                                     XMul &            xmul,
                                     XAdd &            xadd);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const EqStatus st; //!< status
            const xreal_t  xi; //!< required xi

        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            Y_Disable_Assign(Aftermath);
            Aftermath OnProdOnly(XWritable &, Components &, const xreal_t, XMul &);
#endif
            
        };

    }

}

#endif // !Y_Chemical_Aftermath_Included


//! \file

#ifndef Y_Coven_Univocal_Included
#define Y_Coven_Univocal_Included 1

#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace Coven
    {
        

        //______________________________________________________________________
        //
        //
        //
        //! Computing univocal vector representations
        //
        //
        //______________________________________________________________________
        struct Univocal
        {

            static const unsigned LEFT_UNTOUCHED = 0x00;                            //!< alias
            static const unsigned SIMPLIFICATION = 0x01;                            //!< alias
            static const unsigned OPPOSITE_SIGNS = 0x02;                            //!< alias
            static const unsigned COUPLED_UPDATE = SIMPLIFICATION | OPPOSITE_SIGNS; //!< alias

            //! check if opposite signs are to be taken
            /**
             \param numPos    number of positive signs
             \param numNeg    number of negative signs
             \param firstSign first non zero sign if found
             \return (numNeg>numPos) || ( (numPos==numNeg) && firstSign == Negative )
             */
            static
            unsigned OppositeSigns(const size_t numPos,
                                   const size_t numNeg,
                                   const SignType firstSign) noexcept;

            //! make univocal apz vector
            /**
             \param array any apz vector
             \return true if not nul or empty vector
             */
            static bool Make( Writable<apz> &array );

            //! make univocal apz vector from apq vector
            /**
             \param source any      apq vector
             \param target univocal apz vector
             \return true if not nul or empty vector
             */
            static bool Make( Writable<apz> &target, const Readable<apq> &source );

        };

    }
}

#endif // !Y_Coven_Univocal_Included


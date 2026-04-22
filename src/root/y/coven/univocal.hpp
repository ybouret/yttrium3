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

            //! make univocal apz vector
            /**
             \param array any apz vector
             \return true if not nul or empty vector
             */
            static bool Make( Writable<apz> &array );


            static bool Make( Writable<apz> &target, const Readable<apq> &source );

        };

    }
}

#endif // !Y_Coven_Univocal_Included



//! \file

#ifndef Y_BZ2_Input_Included
#define Y_BZ2_Input_Included 1

#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace BZ2
    {
        //______________________________________________________________________
        //
        //
        //
        //! Input gzFile
        //
        //
        //______________________________________________________________________
        class Input : public InputStream
        {
        public:
            class Code;

            virtual ~Input() noexcept;
        private:
            Y_Disable_Copy_And_Assign(Input);
            Code * const code;
        };
    }
}

#endif // !Y_BZ2_Input_Included



//! \file

#ifndef Y_BZ2_Input_Included
#define Y_BZ2_Input_Included 1

#include "y/stream/input.hpp"
#include "y/libc/stdin.hpp"

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

            explicit Input(const String &,     const int small=0);
            explicit Input(const char * const, const int small=0);
            explicit Input(const StdIn_ &,     const int small=0);
            virtual ~Input() noexcept;


            virtual bool   query(char &);
            virtual size_t query(void * const, const size_t);
            virtual void   store(const char);

        private:
            Y_Disable_Copy_And_Assign(Input);
            
            Code * const code;

            

        };
    }
}

#endif // !Y_BZ2_Input_Included


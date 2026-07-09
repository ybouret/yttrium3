
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
        //! Input bzFile
        //
        //
        //______________________________________________________________________
        class Input : public InputStream
        {
        public:
            class Code;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Input(const String &,     const int small=0); //!< open file \param small 0 or 1
            explicit Input(const char * const, const int small=0); //!< open file \param small 0 or 1
            explicit Input(const StdIn_ &,     const int small=0); //!< open stdin \param small 0 or 1
            virtual ~Input() noexcept;                             //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool   query(char &);
            virtual size_t query(void * const, const size_t);
            virtual void   store(const char);

        private:
            Y_Disable_Copy_And_Assign(Input); //!< discarded
            Code * const code;                //!< inner code
        };
    }
}

#endif // !Y_BZ2_Input_Included


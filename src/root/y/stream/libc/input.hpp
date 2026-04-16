
//! file

#ifndef Y_InputFile_Included
#define Y_InputFile_Included 1


#include "y/stream/input.hpp"
#include "y/libc/stdin.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Input File based on Libc::InputFile
    //
    //
    //__________________________________________________________________________
    class InputFile : public InputStream
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param name regular file name of Y_STDIN
        template <typename NAME> inline
        explicit InputFile(const NAME &name) :
        InputStream(name),
        code( OpenRegular(title) )
        {
        }
        explicit InputFile(const StdIn_ &); //!< use stdin
        virtual ~InputFile() noexcept;      //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool query(char &);

    private:
        Y_Disable_Copy_And_Assign(InputFile); //!< discarded
        void * const code; //!< inner code

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        static void * OpenRegular(const String &);
        static void * OpenStdIn();
#endif

    };
}

#endif // !Y_InputFile_Included


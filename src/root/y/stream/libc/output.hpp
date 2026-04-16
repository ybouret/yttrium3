
//! file

#ifndef Y_OutputFile_Included
#define Y_OutputFile_Included 1


#include "y/stream/output.hpp"
#include "y/libc/stdout.hpp"
#include "y/libc/stderr.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Output File from Libc
    //
    //
    //__________________________________________________________________________
    class OutputFile : public OutputStream
    {

    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param name for title \param append true for append mode
        template <typename NAME> inline
        explicit OutputFile(const NAME &name, const bool append = false) :
        OutputStream(name),
        code( OpenRegular(name,append) )
        {
        }
        explicit OutputFile(const StdOut_ &); //!< use stdout
        explicit OutputFile(const StdErr_ &); //!< use stderr
        virtual ~OutputFile() noexcept;       //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void write(const char);
        virtual void write(const void * const, const size_t);
        virtual void flush();

        //______________________________________________________________________
        //
        //
        // Materials
        //
        //______________________________________________________________________
    private:
        Y_Disable_Copy_And_Assign(OutputFile); //!< discarded
        void * const code; //!< inner Libc::OutputFile

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        static void * OpenRegular(const String &fileName, const bool append);
        static void * OpenStdOut();
        static void * OpenStdErr();
#endif

    };

}


#endif // !Y_OutputFile_Included

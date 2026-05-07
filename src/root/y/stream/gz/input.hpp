//! \file

#ifndef Y_GZ_Input_Included
#define Y_GZ_Input_Included 1

#include "y/stream/input.hpp"
#include "y/stream/gz/file.hpp"
#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    namespace GZ
    {
        //______________________________________________________________________
        //
        //
        //
        //! Input gzFile
        //
        //
        //______________________________________________________________________
        class Input : public InputStream, public File
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const Mode; //!< "r"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //_________________________________________________________________

            //! open gzFile \param name compatible file name
            template <typename NAME> inline
            explicit Input(const NAME & name) :
            InputStream(name),
            File(title->c_str(), Mode),
            buff()
            {
            }

            //! cleanup
            virtual ~Input() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool   query(char &);
            virtual void   store(const char);
            virtual size_t query(void * const, const size_t );

        private:
            Y_Disable_Copy_And_Assign(Input); //!< discarded
            IO::Chars buff;                   //!< buffer of decompressed char
        };

    }

}
#endif // !Y_GZ_Input_Included


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
        class Input : public InputStream, public File
        {
        public:
            static const char * const Mode;
            template <typename NAME> inline
            explicit Input(const NAME & name) :
            InputStream(name),
            File(title->c_str(), Mode)
            {
            }

            virtual ~Input() noexcept;

            virtual bool   query(char &);
            virtual void   store(const char);
            virtual size_t query(void * const, const size_t );

        private:
            Y_Disable_Copy_And_Assign(Input);
            IO::Chars buff;
        };

    }

}
#endif // !Y_GZ_Input_Included


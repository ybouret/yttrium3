
//! \file

#ifndef Y_GZ_Output_Included
#define Y_GZ_Output_Included 1

#include "y/stream/output.hpp"
#include "y/stream/gz/file.hpp"

namespace Yttrium
{
    namespace GZ
    {
        //______________________________________________________________________
        //
        //
        //
        //! Outut gzFile
        //
        //
        //______________________________________________________________________
        class Output : public OutputStream, public File
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! precomputed modes \param level clamped [0:9] \return "w[0-9]"
            static const char * GetMode(const int level) noexcept;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! open file \param name compatible name \param level compression
            template <typename NAME> inline
            explicit Output(const NAME &name, const int level=7) :
            OutputStream(name),
            File(title->c_str(),GetMode(level))
            {

            }

            //! cleanup
            virtual ~Output() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void write(const char);
            virtual void flush();
            virtual void write(const void * const, const size_t);

        private:
            Y_Disable_Copy_And_Assign(Output); //!< cleanup
        };
    }

}

#endif // !Y_GZ_Output_Included


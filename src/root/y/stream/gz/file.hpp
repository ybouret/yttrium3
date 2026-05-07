//! \file

#ifndef Y_GZ_File_Included
#define Y_GZ_File_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace GZ
    {
        //______________________________________________________________________
        //
        //
        //
        //! Wrapper for gzFile
        //
        //
        //______________________________________________________________________
        class File
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! open gzFile
            /**
             \param fileName file name
             \param mode     "r" or "w[0-9]"
             */
            explicit File(const char * const fileName,
                          const char * const mode);
            
            virtual ~File() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        protected:
            void * const handle; //!< gzFile

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarded
        };
    }
}

#endif // !Y_GZ_File_Included


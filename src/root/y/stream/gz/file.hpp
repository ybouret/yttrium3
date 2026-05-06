//! \file

#ifndef Y_GZ_File_Included
#define Y_GZ_File_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace GZ
    {
        class File
        {
        public:
            explicit File(const char * const fileName,
                          const char * const mode);
            
            virtual ~File() noexcept;
            
        protected:
            void * const handle;

        private:
            Y_Disable_Copy_And_Assign(File);
        };
    }
}

#endif // !Y_GZ_File_Included


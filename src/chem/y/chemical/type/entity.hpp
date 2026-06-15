
//! \file

#ifndef Y_Chemical_Entity_Included
#define Y_Chemical_Entity_Included 1

#include "y/string.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Basic named entity
        //
        //
        //______________________________________________________________________
        class Entity
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit       Entity();               //!< setup without name
            explicit       Entity(const String &); //!< setup with name
            virtual       ~Entity()    noexcept;   //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key() const noexcept;   //!< \return key

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const String name;                     //!< name

        private:
            Y_Disable_Copy_And_Assign(Entity); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Entity_Included

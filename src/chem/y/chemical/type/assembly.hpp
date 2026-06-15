
//! \file

#ifndef Y_Chemical_Assembly_Included
#define Y_Chemical_Assembly_Included 1

#include "y/chemical/type/entity.hpp"
#include "y/format/justify.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Helper to format entities
        //
        //
        //______________________________________________________________________
        class Assembly
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Assembly()        noexcept; //!< setup
            virtual ~Assembly()        noexcept; //!< cleanup
            Assembly(const Assembly &) noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! update with
            void enroll(const Entity &) noexcept;

            //! pretty justified print \return output stream
            std::ostream & print(std::ostream &, const Entity &, const Justify::Type = Justify::Left) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t width; //!< max name length
        private:
            Y_Disable_Assign(Assembly); //!< discarded

        };
    }

}

#endif // !Y_Chemical_Assembly_Included

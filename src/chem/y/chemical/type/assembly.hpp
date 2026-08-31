
//! \file

#ifndef Y_Chemical_Assembly_Included
#define Y_Chemical_Assembly_Included 1

#include "y/chemical/type/indexed.hpp"
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

            //! update with an entity
            void enroll(const Entity &) noexcept;

            //! reset width
            void reset() noexcept;

            //! pretty justified print \return output stream
            std::ostream & print(std::ostream &, const Entity &, const Justify::Type = Justify::Left) const;

            //! display a list of data from array
            template <typename HLIST, typename ARRAY> inline
            void display(std::ostream &os, const HLIST &list,
                         const char * const pfx,
                         ARRAY &            A,
                         const Level        L,
                         const char * const sfx) const
            {
                for(const typename HLIST::NodeType *node=list->head;node;node=node->next)
                {
                    if(pfx) os << pfx;
                    print(os,(**node));
                    if(sfx) os << sfx;
                    os << " = " << (**node)(A,L) << std::endl;
                }
            }

            //! display a list of transformed data from array
            template <typename HLIST, typename ARRAY, typename PROC> inline
            void display(std::ostream &os, const HLIST &list,
                         const char * const pfx,
                         ARRAY &            A,
                         const Level        L,
                         const char * const sfx,
                         PROC &             proc) const
            {
                for(const typename HLIST::NodeType *node=list->head;node;node=node->next)
                {
                    if(pfx) os << pfx;
                    print(os,(**node));
                    if(sfx) os << sfx;
                    os << " = " << proc( (**node)(A,L) ) << std::endl;
                }
            }



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

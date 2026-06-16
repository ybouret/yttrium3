
//! \file

#ifndef Y_Chemical_Indexed_Included
#define Y_Chemical_Indexed_Included 1

#include "y/chemical/type/entity.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Index level
        //
        //
        //______________________________________________________________________
        enum Level
        {
            TopLevel, //!< top-level for Library and Equilibriau
            SubLevel, //!< sub-level for Clusters
            AuxLevel  //!< aux-level
        };

        //______________________________________________________________________
        //
        //
        //
        //! Indexed entities
        //
        //
        //______________________________________________________________________
        class Indexed : public Entity
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned Levels = AuxLevel; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Indexed(const size_t);                //!< setup without name
            explicit Indexed(const String &,const size_t); //!< setup with name
            virtual ~Indexed() noexcept;                   //!< cleanup

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________

            //! \param arr array \param L level \return arr[ indx[L] ]
            template <typename ARRAY> inline
            typename ARRAY::Type & operator()(ARRAY &arr, const Level L) const noexcept
            {
                assert(indx[L]>0); assert(indx[L]<=arr.size());
                return arr[ indx[L] ];
            }

            //! \param arr array \param L level \return arr[ indx[L] ]
            template <typename ARRAY> inline
            typename ARRAY::ConstType & operator()(const ARRAY &arr, const Level L) const noexcept
            {
                assert(indx[L]>0); assert(indx[L]<=arr.size());
                return arr[ indx[L] ];
            }

            static SignType TopLevelCompare(const Indexed &lhs, const Indexed &rhs) noexcept;

            template <typename HLIST> static inline
            void SubLabel(HLIST &hlist) noexcept
            {
                size_t i = 1;
                for(typename HLIST::NodeType *node=hlist->head;node;node=node->next,++i)
                    Coerce((**node).indx[SubLevel]) = i;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t indx[Levels]; //!< current indices

        private:
            Y_Disable_Copy_And_Assign(Indexed); //!< discarded
            void setup(const size_t) noexcept;  //!< setup helper
        };

    }

}

#endif // !Y_Chemical_Indexed_Included



//! \file

#ifndef Y_Coven_Finder_Included
#define Y_Coven_Finder_Included 1

#include "y/coven/family.hpp"

namespace Yttrium
{

    namespace Coven
    {
        //______________________________________________________________________
        //
        //
        //
        //! Embeded finder of free families
        //
        //
        //______________________________________________________________________
        class Finder : public CountedObject, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Finder(const size_t dims); //!< setup \param dims space dimensions
            virtual ~Finder() noexcept;         //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void free() noexcept;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! check if arrays increase the family size
            /**
             \param arr a compatible array
             \return true if (ortho part of ) array was added to family
             */
            template <typename READABLE> inline
            bool accepts(READABLE &arr) {
                Vector * const v = family.accepted(arr);
                if(!v) return false;
                family.grow(v);
                return true;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            const Metrics metrics; //!< from dims
            VCache        vcache;  //!< from metrics
            Family        family;  //!< from vcache

        public:
            const size_t &size;    //!< alias to family->size (a.k.a current result)

        private:
            Y_Disable_Copy_And_Assign(Finder); //!< discarded
        };

    }

}

#endif // !Y_Coven_Finder_Included


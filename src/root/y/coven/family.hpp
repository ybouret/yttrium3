
//! \file

#ifndef Y_Coven_Family_Included
#define Y_Coven_Family_Included 1

#include "y/coven/vcache.hpp"
#include "y/ability/logging.hpp"

namespace Yttrium
{

    namespace Coven
    {
        //______________________________________________________________________
        //
        //
        //
        //! Family of orthogonals vectors
        //
        //
        //______________________________________________________________________
        class Family :
        public Object,
        public Metrics,
        public Recyclable,
        public Logging
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Family(VCache &) noexcept; //!< setup with PERSISTENT cache
            virtual ~Family()         noexcept; //!< cleanup
            Family(const Family &);             //!< duplicate

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void free() noexcept;
            virtual void toXML(XML::Log &) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! check if a vector can contribute to the family
            /**
             \param a compatible source vector
             \return remaining, not zero orthogonal vector, NULL otherwise
             */
            template <typename READABLE>
            Vector * accepted(READABLE &a)
            {
                switch(quality)
                {
                    case Degenerate:
                        assert(0==list.size);
                        return acceptedFirst(a);

                    case TotalSpace:
                        assert(dimension==list.size);
                        return 0;

                    case Fragmental:
                    case HyperPlane:
                        break;
                }

                assert(list.size>0);
                assert(list.size<dimension);

                

                return 0;
            }

            //! insert an accepted vector \param v valid vector (from accepted)
            void grow(Vector * const v) noexcept;


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Vectors  list;    //!< current vectors
            VCache       & pool;    //!< PERSISTENT cache
            const Quality  quality; //!< current quality
            Family *       next;    //!< for list/pool
            Family *       prev;    //!< for list

        private:
            Y_Disable_Assign(Family); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            void free_() noexcept;
            template <typename READABLE> inline
            Vector * acceptedFirst( READABLE &a )
            {
                Vector * const v = pool.query();
                try
                {
                    if( v->ld(a) )
                        return v;
                    else {
                        pool.store(v);
                        return 0;
                    }
                } catch(...) { pool.store(v); throw; }
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };
    }

}

#endif // !Y_Coven_Family_Included

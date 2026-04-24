//! \file

#ifndef Y_Memory_Classified_Included
#define Y_Memory_Classified_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/libc/block/zero.h"
#include "y/libc/block/zeroed.h"
#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! buffer to hold space for types
        //
        //
        //______________________________________________________________________
        template <typename T, typename ALLOCATOR>
        class Classified : public Memory::ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param numBlocks number of items to hold
            inline explicit Classified(const size_t numBlocks) :
            space(numBlocks),
            count(numBlocks),
            bytes(0),
            entry( AcquireMem(count,bytes) )
            {
                assert(count>=space);
                assert( Y_TRUE == Yttrium_Zeroed(entry,bytes) );
            }
            
            //! cleanup
            inline virtual ~Classified() noexcept
            {
                static ALLOCATOR & mgr = ALLOCATOR::Location();
                Yttrium_BZero(entry,bytes);
                mgr.releaseAs(entry,count,bytes);
                Coerce(space) = 0;
            }


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const void * ro()     const noexcept { return entry; }
            virtual size_t       length() const noexcept { return bytes; }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param indx indx in [0:space-1] \return location of indx-th item
            inline MutableType * operator()(const size_t indx) noexcept
            {
                assert(indx<space);
                return entry+indx;
            }

            //! \param indx indx in [0:space-1] \return location of const indx-th item
            inline ConstType * operator()(const size_t indx) const noexcept
            {
                assert(indx<space);
                return entry+indx;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t space; //!< number of items
        private:
            Y_Disable_Copy_And_Assign(Classified); //!< discarded
            size_t        count; //!< allocated capacity
            size_t        bytes; //!< allocated bytes
            MutableType * entry; //!< allocated first item location

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static inline MutableType * AcquireMem(size_t &numItems, size_t &numBytes)
            {
                static ALLOCATOR & mgr = ALLOCATOR::Instance();
                return mgr.template acquireAs<MutableType>(numItems,numBytes);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Memory_Classified_Included


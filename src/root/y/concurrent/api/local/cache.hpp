
//! \file

#ifndef Y_Concurrent_LocalCache_Included
#define Y_Concurrent_LocalCache_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Cache to dispatch to Subdivisions
        //
        //
        //______________________________________________________________________
        class LocalCache : public CountedObject, public Memory::ReadWriteBuffer
        {
        public:
            class Code;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit LocalCache();           //!< setup emtpy
            virtual ~LocalCache() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const void * ro()     const noexcept;
            virtual size_t       length() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methids
            //
            //__________________________________________________________________

            //! ensure internal memory
            /**
             \param blockSize blockSize>0, will be aligbned
             \param numBlocks numBlocks>0, a.k.a num threads
             \return updated *this
             */
            LocalCache & ensure(const size_t blockSize, const size_t numBlocks);

            //! ensure internal memory for given type
            /**
             \param numBlocks numBlocks>0, a.j.a num threads
             \return update *this
             */
            template <typename T> inline
            LocalCache & ensure(const size_t numBlocks) {
                return ensure(sizeof(T),numBlocks);
            }




        private:
            Y_Disable_Copy_And_Assign(LocalCache); //!< discard
            Code * const code;                     //!< inner code
        };
    }

}

#endif // !Y_Concurrent_LocalCache_Included

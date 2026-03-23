//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1


#include "y/config/setup.hpp"
#include "y/core/max.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Memory Allocator interface
        //
        //
        //______________________________________________________________________
        class Allocator
        {
        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Allocator() noexcept; //!< setup

        public:
            virtual ~Allocator() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________

            //! acquire memory \param blockSize request, updated \return required memoy
            virtual void * acquire(size_t & blockSize)  = 0;

            //! release bytes \param blockAddr previously acquired block \param blockSize previously acquired bytes
            virtual void   release(void * & blockAddr, size_t &blockSize) noexcept = 0;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! helper to acquire array of objects
            /**
             \param count minimal count of objects (set to 1 at least)
             \param bytes acquired bytes, should be initially 0
             \return memory with count and bytes
             */
            template <typename T> inline
            T * acquireAs(size_t &count, size_t &bytes)
            {
                static const size_t MinCount = 1;
                assert(bytes<=0);
                bytes = InSituMax(count,MinCount) * sizeof(T);
                try {
                    void * const addr = acquire(bytes);
                    assert(0!=addr);
                    assert(bytes>=count*sizeof(T));
                    count = bytes/sizeof(T);
                    return static_cast<T*>(addr);
                } catch(...) { assert(0==bytes); count = 0; }
            }

            //! helper to release array of objects
            /**
             \param types acquired objects
             \param count number of objectes
             \param bytes matching bytes
             */
            template <typename T> inline
            void releaseAs(T * &types, T & count, size_t & bytes) noexcept
            {
                assert(0!=types);
                assert(count>0);
                assert(bytes>=sizeof(T)*count);
                {
                    void * addr = (void*)types;
                    release(addr,bytes); assert(0==bytes);
                }
                types = 0;
                count = 0;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            char * createText(const char * const text, size_t &blockSize);
            void   deleteText(char * &text,  size_t &blockSize) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Allocator); //!< discarded
        };
    }
}

#endif // !Y_Memory_Allocator_Included


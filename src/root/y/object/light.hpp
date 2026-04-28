
//! \file

#ifndef Y_LightObject_Included
#define Y_LightObject_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //!  base class for short-lived, light objects
    //
    //
    //__________________________________________________________________________
    class LightObject
    {
    public:
        class Factory;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit LightObject() noexcept; //!< setup
        virtual ~LightObject() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Allocators
        //
        //______________________________________________________________________

        //______________________________________________________________________
        //
        // single object new/delete
        //______________________________________________________________________

        //! acquire memory for new()
        /**
         \param blockSize POSITIVE block size
         \return allocated memory
         */
        static void * operator new(const size_t blockSize);

        //! release previously acquire memory
        /**
         \param blockAddr block address
         \param blockSize block size
         */
        static void   operator delete(void * const blockAddr, const size_t blockSize) noexcept;

        //______________________________________________________________________
        //
        // multiple objects new[]/delete[]
        //______________________________________________________________________
        //! acquire memory for new[]()
        /**
         \param blockSize POSITIVE block size
         \return allocated memory
         */
        static void * operator new    [](const size_t blockSize);

        //! release previously acquired memory
        /**
         \param blockAddr block address
         \param blockSize block size
         */
        static void   operator delete [](void * const blockAddr, const size_t blockSize) noexcept;

        //______________________________________________________________________
        //
        // placement new()/delete()
        //______________________________________________________________________

        //! placement new()
        /**
         \param blockSize positive block size
         \param blockAddr a valid block address
         \return zeroed blockAddr
         */
        static void *operator new(const size_t blockSize, void * const blockAddr) noexcept;

        //! placement delete
        static void  operator delete(void * const , void * const)                 noexcept;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return zombie memory for given type
        template <typename T> static inline
        T * AcquireZombie() { return static_cast<T*>(operator new (sizeof(T))); }

        //! release zombie memory \param zombie zombie type
        template <typename T> static inline
        void ReleaseZombie(T * const zombie) noexcept { operator delete(zombie,sizeof(T));  }

    private:
        Y_Disable_Copy_And_Assign(LightObject); //!< discarded
    };
}

#endif // !Y_LightObject_Included


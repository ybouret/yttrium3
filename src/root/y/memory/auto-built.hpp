//! \file

#ifndef Y_Memory_AutoBuilt_Included
#define Y_Memory_AutoBuilt_Included 1

#include "y/memory/auto-build.hpp"
#include "y/type/args.hpp"
#include "y/type/procedural.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! storing args for AutoBuit
        //
        //
        //______________________________________________________________________
        class AutoBuiltArgs
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit AutoBuiltArgs() noexcept; //!< setup with no arguments
            virtual ~AutoBuiltArgs() noexcept; //!< setup with arguments

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename U> inline
            explicit AutoBuiltArgs(U &u) noexcept : arg1( (void *) &u ), arg2(0), arg3(0) {}


            template <typename U, typename V> inline
            explicit AutoBuiltArgs(U &u, V &v) noexcept : arg1( (void *) &u ), arg2( (void*) &v ), arg3(0) {}

            template <typename U, typename V, typename W> inline
            explicit AutoBuiltArgs(U &u, V &v, W &w) noexcept : arg1( (void *) &u ), arg2( (void*) &v ), arg3( (void*)&w ) {}
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            void * const arg1; //!< first  argument
            void * const arg2; //!< second argument
            void * const arg3; //!< third  argument

        protected:
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            AutoBuiltArgs *args() noexcept; //!< for AutoBuilt args \return this



        private:
            Y_Disable_Copy_And_Assign(AutoBuiltArgs); //!< discarded
        };

        //______________________________________________________________________

        //______________________________________________________________________
        //
        //
        //
        //! Built array of types with user's specifications
        //
        //
        //______________________________________________________________________
        template <typename T>
        class AutoBuilt : public AutoBuiltArgs, public AutoBuild
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             */
            inline explicit AutoBuilt(void * const userBlockAddr,
                                      const size_t userNumBlocks) :
            AutoBuiltArgs(),
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuild0)
            {
            }

            //! setup with one argument constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             - MutableType(arg1) called for each type
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             \param arg1          argument to build
             */
            template <typename U>
            inline explicit AutoBuilt(void * const userBlockAddr,
                                      const size_t userNumBlocks,
                                      U &          arg1) :
            AutoBuiltArgs(arg1),
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuild1<U>,args())
            {
            }

            //! setup with two arguments constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             - MutableType(arg1,arg2) called for each type
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             \param arg1          argument to build
             \param arg2          argument to build
             */
            template <typename U, typename V>
            inline explicit AutoBuilt(void * const userBlockAddr,
                                      const size_t userNumBlocks,
                                      U &          arg1,
                                      V &          arg2) :
            AutoBuiltArgs(arg1,arg2),
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuild2<U,V>,args())
            {
            }

            //! setup with three arguments constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             - MutableType(arg1,arg2,arg3) called for each type
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             \param arg1          argument to build
             \param arg2          argument to build
             \param arg3          argument to build
             */
            template <typename U, typename V, typename W>
            inline explicit AutoBuilt(void * const userBlockAddr,
                                      const size_t userNumBlocks,
                                      U &          arg1,
                                      V &          arg2,
                                      W &          arg3) :
            AutoBuiltArgs(arg1,arg2,arg3),
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuild3<U,V,W>,args())
            {
            }


            //! setup with one indexed argument constructor
            /**
             - userBlockAddr must have at least userNumBlocks * sizeof(T)
             - MutableType(arr[indx]) called for each type
             \param userBlockAddr where to build
             \param userNumBlocks blocks to build
             \param arr           array[1:numBlocks] to build
             */
            template <typename ARR>
            inline explicit AutoBuilt(const Procedural_ &,
                                      void * const userBlockAddr,
                                      const size_t userNumBlocks,
                                      ARR &        arr) :
            AutoBuild(userBlockAddr,userNumBlocks,sizeof(T),OnDelete,OnBuildN<ARR>,(void*)&arr)
            {
            }

            //! cleanup
            inline virtual ~AutoBuilt() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(AutoBuilt); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            static inline void OnBuild0(void * const addr)
            {
                new (addr) MutableType();
            }

            static inline void OnDelete(void * const addr) noexcept
            {
                assert(0!=addr);
                Destruct( static_cast<MutableType *>(addr) );
            }

            template <typename U>
            static inline void OnBuild1(void * const addr, void * const args)
            {
                assert(0!=args);
                AutoBuiltArgs &data = *static_cast<AutoBuilt *>(args); assert(data.arg1);
                U & u  = *static_cast<U*>(data.arg1);
                new (addr) MutableType(u);
            }

            template <typename U, typename V>
            static inline void OnBuild2(void * const addr, void * const args)
            {
                assert(0!=args);
                AutoBuiltArgs &data = *static_cast<AutoBuilt *>(args); assert(data.arg1);
                U & u  = *static_cast<U*>(data.arg1);                  assert(data.arg2);
                V & v =  *static_cast<V*>(data.arg2);
                new (addr) MutableType(u,v);
            }

            template <typename U, typename V, typename W>
            static inline void OnBuild3(void * const addr, void * const args)
            {
                assert(0!=args);
                AutoBuiltArgs &data = *static_cast<AutoBuilt *>(args); assert(data.arg1);
                U & u  = *static_cast<U*>(data.arg1);                  assert(data.arg2);
                V & v =  *static_cast<V*>(data.arg2);                  assert(data.arg3);
                W & w =  *static_cast<W*>(data.arg3);
                new (addr) MutableType(u,v,w);
            }

            template <typename ARR>
            static inline void OnBuildN(void *const  addr,
                                        void * const arg1,
                                        const size_t indx)
            {
                assert(0!=arg1);
                assert(indx>0);
                ARR &arr  = *static_cast<ARR*>(arg1);
                new (addr) MutableType(arr[indx]);
            }

#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Memory_AutoBuilt_Included


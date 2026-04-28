//! \file

#ifndef Y_Handy_SharedCache_Included
#define Y_Handy_SharedCache_Included 1

#include "y/handy/cache/object.hpp"
#include "y/pointer/arc.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Handy
    {

        //______________________________________________________________________
        //
        //
        //
        //! Shared cache for multiple objects level pooling
        //
        //
        //______________________________________________________________________
        template <typename NODE, typename THREADING_POLICY>
        class SharedCache
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_HandyCache_Decl();                                  //!< aliases
            typedef ObjectCache<NODE,ThreadingPolicy> InnerCache; //!< alias

            //__________________________________________________________________
            //
            //
            //! Inner code
            //
            //__________________________________________________________________
            class Code : public CountedObject, public InnerCache
            {
            public:
                inline explicit Code() : CountedObject(), InnerCache() {} //!< setup
                inline virtual ~Code() noexcept {}                        //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(Code); //!< discarded
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with new cache
            inline explicit SharedCache() : code( new Code() )
            {
            }

            //! duplicate shared cache \param sc another shared cache
            inline SharedCache(const SharedCache &sc) noexcept : code( sc.code )
            {
            }

            //! cleanup
            inline virtual ~SharedCache() noexcept
            {
            }

            inline InnerCache       * operator->()       noexcept { return & *code; } //!< \return API
            inline const InnerCache * operator->() const noexcept { return & *code; } //!< \return API
            inline Lockable &         operator*()        noexcept { return   *code; } //!< \return lockable

        private:
            Y_Disable_Assign(SharedCache); //!< discarded
            ArcPtr<Code> code;             //!< inner code
        };

    }

}

#endif // !Y_Handy_SharedCache_Included


//! \file

#ifndef Y_Object_Factory_Included
#define Y_Object_Factory_Included 1

#include "y/object.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    class Object :: Factory : public Singleton<Factory,ClassLockPolicy>
    {
    public:
        static const char * const CallSign;
        static const Longevity    LifeTime = LifeTimeFor::ObjectFactory;
        typedef ClassLockPolicy   Policy;
        
        enum Model
        {
            None, //!< NULL
            Slim, //!< uses Small
            Fair, //!< uses Pooled
            Vast, //!< uses Dyadic
            Huge  //!< uses Global
        };
        static Model ModelFor(const size_t blockSize) noexcept;

        static size_t SlimCompress(const size_t blockSize) noexcept;

        void * query(const size_t blockSize);
        void   store(void * const blockAddr, const size_t blockSize) noexcept;

    private:
        Y_Disable_Copy_And_Assign(Factory);
        friend class Singleton<Factory,Policy>;
        explicit Factory();
        virtual ~Factory() noexcept;
    };
}


#endif // !Y_Object_Factory_Included



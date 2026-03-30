#include "y/concurrent/fake-lock.hpp"
#include "y/pointer/locking-proxy.hpp"
#include "y/utest/run.hpp"


namespace Yttrium
{

    template <typename T>
    class AutoLocking 
    {
    public:
        Y_Args_Expose(T,Type);
        typedef Smart::LockingProxy<Type>      ReturnType;      //!< alias
        typedef Smart::LockingProxy<ConstType> ConstReturnType; //!< alias

        inline explicit AutoLocking( Type & obj ) noexcept :
        host( &obj )
        {
        }
        
        inline virtual ~AutoLocking() noexcept {}

        inline ReturnType      operator->()       noexcept { assert(host); return ReturnType(host); }
        inline ConstReturnType operator->() const noexcept { assert(host); return ConstReturnType(host); }


    private:
        Y_Disable_Copy_And_Assign(AutoLocking);
        Type * const host;
    };

}

using namespace Yttrium;



namespace
{


    class Dummy : public Concurrent::FakeLock, public AutoLocking<Dummy>
    {
    public:
        inline Dummy() noexcept : Concurrent::FakeLock(), AutoLocking<Dummy>(*this)
        {
        }

        inline ~Dummy() noexcept
        {

        }

        void display()
        {
            std::cerr << "display unlocked " << *this << std::endl;
        }

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };
}

Y_UTEST(concurrent_fake_lock)
{
    Concurrent::FakeLock::Verbose = true;

    {
        Concurrent::FakeLock fl;
        std::cerr << "Using" << fl << std::endl;
        {
            Y_Lock(fl);
            {
                Y_Lock(fl);
            }
        }
        std::cerr << std::endl;
    }

    {
        Dummy dummy;
        dummy.display();
        dummy->display();
    }

    std::cerr << "End..." << std::endl;
}
Y_UDONE()



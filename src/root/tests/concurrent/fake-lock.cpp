#include "y/concurrent/fake-lock.hpp"
#include "y/ability/auto-locking.hpp"
#include "y/utest/run.hpp"




using namespace Yttrium;



namespace
{


    class Dummy : public Concurrent::FakeLock, public AutoLocking<Dummy>
    {
    public:
        inline Dummy() noexcept : Concurrent::FakeLock(), AutoLocking<Dummy>( self() )
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
        inline Dummy& self() noexcept { return *this;  }
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



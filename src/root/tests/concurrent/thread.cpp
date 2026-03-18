#include "y/concurrent/thread.hpp"
#include "y/ability/lockable.hpp"
#include "y/utest/run.hpp"

#include <cassert>

using namespace Yttrium;

namespace
{
    struct Parameters
    {
        Lockable * sync;
    };

    static inline
    void DoSomething(void * const args)
    {
        Y_ASSERT(args);
        Parameters & params = *static_cast<Parameters *>(args);
        {
            Y_Lock(*params.sync);
            (std::cerr << "In Thread!" << std::endl).flush();
        }
    }

    class ParaData
    {
    public:
        typedef void (ParaData::*Meth)(void);

        template <typename OBJECT, typename METHOD> inline
        explicit ParaData(OBJECT &object, METHOD method) noexcept :
        host( &object ),
        meth( GetMeth(method) ),
        arg1(0)
        {
        }

        virtual ~ParaData() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(ParaData);
        void * const host;
        Meth         meth;
        void * const arg1;

        template <typename METHOD> static inline
        Meth GetMeth(METHOD method) noexcept
        {
            assert(sizeof(METHOD) == sizeof(Meth));
            union  {
                METHOD M;
                Meth   m;
            } alias = { method };
            return alias.m;
        }

        template <typename METHOD> inline
        METHOD getMethod() noexcept
        {
            assert(sizeof(METHOD) == sizeof(Meth));
            union  {
                Meth   m;
                METHOD M;
            } alias = { meth };
            return alias.M;
        }


    protected:
        template <typename OBJECT, typename METHOD> static inline
        void Launch(void * const addr)
        {
            assert(addr);
            ParaData &p = *static_cast<ParaData *>(addr);
            OBJECT   &o = *static_cast<OBJECT *>(p.host);
            METHOD    m = p.getMethod<METHOD>();
            (o.*m)();
        }

    };

    class ParaRun : public ParaData, public Concurrent:: Thread
    {
    public:
        template <typename OBJECT, typename METHOD> inline
        explicit ParaRun(OBJECT &object, METHOD method) noexcept :
        ParaData(object,method),
        Thread( Launch<OBJECT,METHOD>, self() )
        {
        }

        virtual ~ParaRun() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(ParaRun);
        ParaData * self() noexcept { return this; }
    };


    class Dummy
    {
    public:
        Dummy()
        {
        }

        ~Dummy() noexcept
        {
        }

        void something(void)
        {
            {
                Y_Giant_Lock();
                std::cerr << "dummy.something" << std::endl;
            }
        }

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };


}

Y_UTEST(concurrent_thread)
{
    Parameters params = { & Lockable::Giant() };
    {
        Concurrent::Thread thread(DoSomething,&params);
        {
            Y_Lock(*params.sync);
            std::cerr << "In Thread Scope" << std::endl;
        }

    }
    {
        Dummy   dum;
        ParaRun run0( dum, & Dummy::something );
    }
    std::cerr << "End Of Program" << std::endl;
}
Y_UDONE()


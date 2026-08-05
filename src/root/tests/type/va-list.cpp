#include "y/type/va-list.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    typedef void (*CProto)(void);

    static inline void doNothing(void)
    {
        std::cerr << "I do nothing.." << std::endl;
    }

    struct DoNothing
    {
        typedef void (DoNothing:: *Proto)(void);

        void call(void)
        {
            doNothing();
        }

    };
}

Y_UTEST(type_va_list)
{

    Y_SIZEOF(Concurrent::VaList::Func);
    Y_SIZEOF(Concurrent::VaList::Meth);
    Y_PRINTV(Concurrent::VaList::BytesForFunc);
    Y_PRINTV(Concurrent::VaList::BytesForMeth);
    Y_PRINTV(Concurrent::VaList::RequiredBytes);
    Y_PRINTV(Concurrent::VaList::RequiredWords);
    Y_SIZEOF(Concurrent::VaList);


    {
        Concurrent::VaList vp;
        Y_CHECK(vp.freeBytes() >= Concurrent::VaList::RequiredBytes );
        Y_PRINTV(vp);

        int a = 8;
        Y_PRINTV( (void*) &a );
        Y_PRINTV(vp<<a);
        Y_PRINTV(vp(doNothing));

        a=7;
        Y_PRINTV( vp.as<const int>() );

        CProto f = vp.func<CProto>();
        f();

    }

    {
        Concurrent::VaList vp;
        DoNothing host;
        Y_PRINTV( (void*) &host );
        Y_PRINTV( vp(host, & DoNothing:: call ) );

        DoNothing        &who = vp.as<DoNothing>();           //Y_CHECK( &who == &host);
        DoNothing::Proto  run = vp.meth<DoNothing::Proto>();  //Y_CHECK( &DoNothing::call == run);

        (who.*run)();

    }




}
Y_UDONE()

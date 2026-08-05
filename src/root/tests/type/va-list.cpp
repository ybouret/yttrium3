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

    Y_SIZEOF(VaList::Func);
    Y_SIZEOF(VaList::Meth);
    Y_PRINTV(VaList::BytesForFunc);
    Y_PRINTV(VaList::BytesForMeth);
    Y_PRINTV(VaList::RequiredBytes);
    Y_PRINTV(VaList::RequiredWords);
    Y_SIZEOF(VaList);


    {
        VaList vp;
        Y_CHECK(vp.freeBytes() >= VaList::RequiredBytes );
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
        VaList    vp;
        DoNothing host;
        Y_PRINTV( (void*) &host );
        Y_PRINTV( vp(host, & DoNothing:: call ) );

        DoNothing        &who = vp.as<DoNothing>();
        DoNothing::Proto  run = vp.meth<DoNothing::Proto>();
        (who.*run)();
    }




}
Y_UDONE()

#include "y/type/va/args.hpp"
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

    std::cerr << "(*) Metrics for VaList: " << std::endl;
    Y_SIZEOF(VaList::Func);
    Y_SIZEOF(VaList::Meth);
    Y_PRINTV(VaList::BytesForFunc);
    Y_PRINTV(VaList::BytesForMeth);
    Y_PRINTV(VaList::RequiredTotal);
    Y_PRINTV(VaList::RequiredBytes);
    Y_PRINTV(VaList::RequiredWords);
    Y_SIZEOF(VaList);
    std::cerr << "(*) Arguments: " << std::endl;
    Y_PRINTV(VaList::MaxFuncArgs);
    Y_PRINTV(VaList::MaxMethArgs);

    {
        VaList vp;
        Y_CHECK(vp.freeBytes() >= VaList::RequiredBytes );
        Y_PRINTV(vp);

        int a = 8;
        Y_PRINTV( (void*) &a );
        Y_PRINTV(vp<<a);
        Y_PRINTV(vp(doNothing));

        a=7;
        VaArgs ap(vp);
        Y_PRINTV( ap.as<const int>() );

        CProto f = ap.func<CProto>();
        f();

    }

    {
        VaList    vp;
        DoNothing host;
        Y_PRINTV( (void*) &host );
        Y_PRINTV( vp(host, & DoNothing:: call ) );

        VaArgs            ap(vp);
        DoNothing        &who = ap.as<DoNothing>();
        DoNothing::Proto  run = ap.meth<DoNothing::Proto>();
        (who.*run)();
    }



}
Y_UDONE()

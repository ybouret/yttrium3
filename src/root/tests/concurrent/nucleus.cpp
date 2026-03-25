#include "y/concurrent/nucleus.hpp"
#include "y/ability/lockable.hpp"
#include "y/utest/run.hpp"
#include "y/stream/xmlog.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_nucleus)
{
    Concurrent::Singulet::Verbose = true;
    {
        Y_Giant_Lock();
    }
    
    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    std::cerr << nucleus.callSign() << " @" << nucleus.lifeTime() << std::endl;

    Concurrent::SystemMutex *mtx = nucleus.acquireSystemMutex();
    nucleus.releaseSystemMutex(mtx);

    bool     verbose = true;
    XML::Log xml(std::cerr,verbose);
    nucleus.toXML(xml);
    
}
Y_UDONE()


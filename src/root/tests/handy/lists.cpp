#include "y/handy/list-proto.hpp"




#include "y/handy/cache/shared.hpp"
#include "y/handy/cache/direct.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/handy/node/light.hpp"
#include "y/handy/node/heavy.hpp"
#include "y/core/rand.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/type/sign.hpp"

using namespace Yttrium;

namespace
{


    template <typename TARGET, typename SOURCE> inline
    void doPush( TARGET &target, Core::Rand  &ran, SOURCE &source )
    {
        for(size_t i=source.size();i>0;--i)
        {
            if( ran.tails() ) target << source[i]; else target >> source[i];
        }
        TARGET tarcpy(target);
        std::cerr << target << " | " << tarcpy << std::endl;

        {
            const size_t n = tarcpy->size/2;
            while( tarcpy.size() > n )
            {
                if( ran.tails() ) tarcpy.popTail(); else tarcpy.popHead();
            }
            target << tarcpy;
            target >> tarcpy;
        }
        std::cerr << "\t" << target << std::endl;
        target->sortBy( Sign::Increasing<typename TARGET::NodeType::MutableType> );
        std::cerr << "\t" << target << std::endl;


    }

    template <typename NODE, typename SOURCE> inline
    void doProc( Core::Rand & ran, SOURCE &v)
    {

        {
            Handy::ListProto<NODE,Handy::DirectCache,SingleThreadedClass> list;
            doPush(list,ran,v);
        }

        {
            Handy::ListProto<NODE,Handy::DirectCache,MultiThreadedObject> list;
            doPush(list,ran,v);
        }

        {
            Handy::ListProto<NODE,Handy::ObjectCache,SingleThreadedClass> list;
            doPush(list,ran,v);
        }

        {
            Handy::ListProto<NODE,Handy::ObjectCache,MultiThreadedObject> list;
            doPush(list,ran,v);
        }

        {
            Handy::SharedCache<NODE,SingleThreadedClass>                  sc;
            Handy::ListProto<NODE,Handy::SharedCache,SingleThreadedClass> list(sc);
            doPush(list,ran,v);
        }

        {
            Handy::SharedCache<NODE,MultiThreadedObject>                  sc;
            Handy::ListProto<NODE,Handy::SharedCache,MultiThreadedObject> list(sc);
            doPush(list,ran,v);
        }

    }

    template <typename T>
    static inline void testProto( Core::Rand &ran )
    {
        const size_t n = ran.in<size_t>(10,20);
        Vector<T>    v(WithAtLeast,n);
        for(size_t i=0;i<n;++i) v << T( ran.in<int>(-10,10) );

        std::cerr << "v=" << v << std::endl;

        doProc< Handy::LightNode<T>, Writable<T> >(ran,v);
        doProc< Handy::HeavyNode<T>, Writable<T> >(ran,v);

    }

}

#include "y/apex/rational.hpp"
Y_UTEST(handy_lists)
{
    Core::Rand ran;
    testProto<int>(ran);
    testProto<apq>(ran);
}
Y_UDONE()


#include "y/string.hpp"
#include "y/concurrent/threaded.hpp"
#include "y/memory/auto-built.hpp"
#include "y/utest/run.hpp"
#include "y/calculus/alignment.hpp"
#include "y/libc/block/zero.h"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/core/list/cxx.hpp"

using namespace Yttrium;


namespace
{
    static const size_t NumThreads = 8;

    class Node : public String
    {
    public:
        typedef CxxList<Node> List;

        explicit Node(const String &s) : String(s), next(0), prev(0)
        {

        }

        virtual ~Node() noexcept
        {
        }


        Node * next;
        Node * prev;

    private:
        Y_Disable_Copy_And_Assign(Node);
    };



    class Testing
    {
    public:

        Testing() : mutex(), cond(), ready(0)
        {}

        ~Testing() noexcept
        {
        }

        void Run()
        {
            mutex.lock();
            (std::cerr << "Entering #" << ready+1 << std::endl).flush();
            if(++ready<NumThreads)
            {
                cond.wait(mutex);
            }
            else
            {
                cond.broadcast();
                (std::cerr << "synchronized!" << std::endl).flush();
            }
            mutex.unlock();

        }

        Concurrent::Mutex      mutex;
        Concurrent::Condition  cond;
        size_t                 ready;
        Node::List             list;

    private:
        Y_Disable_Copy_And_Assign(Testing);

    };
}

#include "y/stream/libc/input.hpp"
Y_UTEST(string_in_threads)
{
    static const size_t Requested = sizeof(Concurrent::Threaded) * NumThreads;
    static void * wksp[ Alignment::WordsGEQ<Requested>::Count ];


    Testing testing;
    if(argc>1)
    {
        InputFile fp(argv[1]);
        String    line;
        while( fp.gets(line) )
        {
            testing.list.pushTail( new Node(line) );
        }
    }
    std::cerr << testing.list << std::endl;


    Memory::AutoBuilt<Concurrent::Threaded> threads(testing, & Testing::Run, Y_BZero(wksp), NumThreads);

}
Y_UDONE()


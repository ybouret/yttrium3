
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/core/max.hpp"
#include "y/concurrent/thread.hpp"
#include "y/memory/buffer/classified.hpp"
#include "y/memory/allocator/archon.hpp"
#include "y/type/destruct.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {

        class Crew:: Code : public Object
        {
        public:
            typedef Memory::Classified<Thread,Memory::Archon> Threads;

            inline explicit Code(const size_t numThreads,
                                 Procedure   &theProc,
                                 Arguments * &theArgs) :
            Object(),
            level( Max<size_t>(numThreads,1) ),
            ready(0),
            inuse(0),
            proc(theProc),
            args(theArgs),
            mutex(),
            cycle(),
            comms(),
            threads( level )
            {
                init();
            }

            inline virtual ~Code() noexcept {
                quit();

            }

            void run() noexcept;

            const size_t level;
            size_t       ready;
            size_t       inuse;
            Procedure   &proc;
            Arguments * &args;
            Mutex        mutex;
            Condition    cycle;
            Condition    comms;
            Threads      threads;

        private:
            Y_Disable_Copy_And_Assign(Code);
            void init();
            void loop() noexcept;
            void quit() noexcept;

            static inline void Launch(void * const args) noexcept
            {
                assert(args);
                static_cast<Code *>(args)->loop();
            }
        };


        void Crew:: Code:: quit() noexcept
        {
            assert(!proc);
            assert(!args);
            assert(!inuse);

            // wake up all (remaining)
            cycle.broadcast();

            // wait for all threads to return
            {
                Y_Lock(mutex);
                if(ready>0) comms.wait(mutex);
                std::cerr << "all done" << std::endl;
            }



            // cleanup
            for(size_t i=0;i<level;++i)
                Destruct( threads(i) );
            
        }

        void Crew:: Code:: init()
        {
            assert(0==ready);
            try
            {
                Code * const code = this;
                for(size_t i=0;i<level;++i)
                {
                    new ( threads(i) ) Thread(Launch,code);
                    {
                        Y_Lock(mutex); if(ready<=i) comms.wait(mutex);
                    }
                }
                (std::cerr << "synchronized" << std::endl);

            }
            catch(...)
            {
                quit();
                throw;
            }
        }

        void Crew:: Code:: loop() noexcept
        {

            //------------------------------------------------------------------
            //
            // starting thread, LOCK mutex
            //
            //------------------------------------------------------------------
            mutex.lock(); assert(ready<level);
            Context context(level,ready,mutex);
            (std::cerr << context << " is ready" << std::endl).flush();
            ++ready;
            comms.signal();
        CYCLE:
            cycle.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a LOCKED mutex
            //
            //------------------------------------------------------------------

            if(!proc)
            {
                (std::cerr << context << " is leaving" << std::endl).flush();
                assert(ready>0);
                if(--ready<=0) comms.signal();
                mutex.unlock();
                return;
            }


            //------------------------------------------------------------------
            //
            // work to do
            //
            //------------------------------------------------------------------
            assert(inuse>0); assert(args);

            mutex.unlock();
            { proc(context,*args); }
            mutex.lock();
            
            assert(inuse>0);
            if(--inuse<=0) comms.signal();
            goto CYCLE;
        }

        void Crew:: Code:: run() noexcept
        {
            assert(proc);
            assert(args);
            assert(!inuse);
            inuse = level;
            cycle.broadcast();
            { Y_Lock(mutex); if(inuse) comms.wait(mutex); }

        }



        Crew:: Crew(const size_t n) :
        code( new Code(n,procedure,arguments) )
        {
            std::cerr << "sizeof(Crew::Code) = " << sizeof(Code) << std::endl;
        }

        Crew:: ~Crew() noexcept
        {
            assert(code);
            Destroy(code);
        }

        void Crew:: run()
        {
            assert(procedure);
            assert(arguments);
            code->run();
        }

    }

}



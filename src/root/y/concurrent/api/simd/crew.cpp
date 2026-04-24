
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/core/max.hpp"
#include "y/concurrent/thread.hpp"
#include "y/memory/buffer/classified.hpp"
#include "y/memory/allocator/archon.hpp"
//#include "y/container/cxx/series.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {

        class Crew:: Code : public Object
        {
        public:
            typedef Memory::Classified<Thread,Memory::Archon> Threads;
            //typedef CxxSeries<Thread> Threads;

            inline explicit Code(const size_t numThreads,
                                 SIMD        &parent) :
            Object(),
            level( Max<size_t>(numThreads,1) ),
            ready(0),
            instr(parent),
            mutex(),
            cycle(),
            comms(),
            threads( level )
            {
                init();
            }

            inline virtual ~Code() noexcept {

            }


            const size_t level;
            size_t       ready;
            SIMD        &instr;
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
                        Y_Lock(mutex);
                        if(ready<=i) comms.wait(mutex);
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
            (std::cerr << "in " << context << std::endl).flush();
            ++ready;
            comms.signal();
            cycle.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a LOCKED mutex
            //
            //------------------------------------------------------------------
            

        }


        SIMD & Crew:: self() noexcept { return *this; }

        Crew:: Crew(const size_t n) :
        code( new Code(n,self()) )
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
            
        }

    }

}



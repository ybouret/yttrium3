
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/core/max.hpp"
#include "y/concurrent/thread.hpp"
#include "y/memory/buffer/classified.hpp"
#include "y/memory/allocator/archon.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Crew:: Code : public Object
        {
        public:
            typedef Memory::Classified<Thread,Memory::Archon> Threads;

            inline explicit Code(const size_t n) :
            Object(),
            level( Max<size_t>(n,1) ),
            ready(0),
            mutex(),
            start(),
            leave()
            {

            }

            inline virtual ~Code() noexcept
            {

            }

            const size_t level;
            size_t       ready;
            Mutex        mutex;
            Condition    start;
            Condition    leave;
            

        private:
            Y_Disable_Copy_And_Assign(Code);

        };



        Crew:: Crew(const size_t n) :
        code( new Code(n) )
        {

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



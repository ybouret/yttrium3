
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Yttrium
{
	namespace Concurrent
	{
		class SystemMutex : public Latch
		{
		public:
			inline explicit SystemMutex() noexcept : mutex()
			{
				::InitializeCriticalSection(mutex());
			}

			inline virtual ~SystemMutex() noexcept
			{
				::LeaveCriticalSection(mutex());
			}

			inline virtual void lock() noexcept
			{
				::EnterCriticalSection(mutex());
			}

			inline virtual void unlock() noexcept
			{
				::LeaveCriticalSection(mutex());
			}

			inline virtual bool tryLock() noexcept
			{
				return TRUE == ::TryEnterCriticalSection(mutex());
			}

			Memory::Single<CRITICAL_SECTION> mutex;

		private:
			Y_Disable_Copy_And_Assign(SystemMutex);
		};


		class SystemCondition
		{
		public:
			inline   SystemCondition()
			{

			}

			inline ~SystemCondition() noexcept
			{

			}

		private:
			Y_Disable_Copy_And_Assign(SystemCondition);
            
		};

	}

}

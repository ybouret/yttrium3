
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

		class SystemThread
		{
		public:
			inline SystemThread(Thread &thread) : tid(0), handle(INVALID_HANDLE_VALUE)
			{
				Y_Giant_Lock();
				handle = ::CreateThread(0, 0, Launch, (void*)&thread, 0, &tid);
				if (!handle)
				{
					throw Windows::Exception(::GetLastError(), "::CreateThread");
				}
			}

			inline ~SystemThread() noexcept
			{
				//Y_Giant_Lock();
				tid = 0;
				if (WAIT_OBJECT_0 != ::WaitForSingleObject(handle, INFINITE))
					Windows::Error::Critical(::GetLastError(), "WaitForSingleObject");
			}

			DWORD  tid;
			HANDLE handle;

		private:
			Y_Disable_Copy_And_Assign(SystemThread);

			static inline DWORD WINAPI Launch(LPVOID args) noexcept
			{
				assert(0 != args);
				Thread& thread = *static_cast<Thread*>(args);
				try 
				{
					thread.proc(thread.args);
				}
				catch (...)
				{

				}
				return 0;
			}
		};
	}

}

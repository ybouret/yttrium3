
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

	}

}

#include "y/concurrent/windows/semaphore.hpp"

namespace Yttrium
{
	namespace Concurrent
	{
		class SystemCondition
		{
		public:
			inline   SystemCondition() :
				cv_lock(),
				cv_waiting(0),
				cv_signals(0),
				cv_wait_sem(),
				cv_done_sem()
			{

			}

			inline ~SystemCondition() noexcept
			{

			}

			inline void wait(SystemMutex& m) noexcept
			{
				/*	Obtain the protection mutex, and increment the number of waiters.
					This allows the signal mechanism to only perform a signal if there
					are waiting threads.
				*/
				cv_lock.lock();
				++cv_waiting;
				cv_lock.unlock();

				/* Unlock the mutex, as is required by condition variable semantics */
				m.unlock();

				/* Wait for a signal */
				cv_wait_sem.wait();


				/* Let the signaler know we have completed the wait, otherwise
				 the signaler can race ahead and get the condition semaphore
				 if we are stopped between the mutex unlock and semaphore wait,
				 giving a deadlock.  See the following URL for details:
				 http://www-classic.be.com/aboutbe/benewsletter/volume_III/Issue40.html
				 */

				cv_lock.lock();
				if (cv_signals > 0)
				{
					/* We always notify the signal thread that we are done */
					cv_done_sem.post();
					--cv_signals;
				}
				--cv_waiting;
				cv_lock.unlock();

				/* Lock the mutex, as is required by condition variable semantics */
				m.lock();
			}

			inline void signal() noexcept
			{
				cv_lock.lock();
				if (cv_waiting > cv_signals)
				{
					++cv_signals;
					cv_wait_sem.post();
					cv_lock.unlock();
					cv_done_sem.wait();
				}
				else
					cv_lock.unlock();
			}

			inline void broadcast() noexcept
			{
				/*	If there are waiting threads not already signalled, then
					signal the condition and wait for the thread to respond.
				*/
				cv_lock.lock();
				if (cv_waiting > cv_signals)
				{
					const int num_waiting = cv_waiting - cv_signals;
					cv_signals = cv_waiting;
					for (int i = 0; i < num_waiting; ++i)
					{
						cv_wait_sem.post();
					}
					/* Now all released threads are blocked here, waiting for us.
					 Collect them all.
					 */
					cv_lock.unlock();
					for (int i = 0; i < num_waiting; ++i)
					{
						cv_done_sem.wait();
					}
				}
				else
				{
					cv_lock.unlock();
				}
			}



		private:
			Y_Disable_Copy_And_Assign(SystemCondition);
			SystemMutex        cv_lock;      /*!< condition lock               */
			int                cv_waiting;   /*!< waiting count                */
			int                cv_signals;   /*!< signals count                */
			Windows::Semaphore cv_wait_sem;  /*!< Win32 semaphore when waiting */
			Windows::Semaphore cv_done_sem;  /*!< Win32 semaphore when done    */
		};

		class SystemThread
		{
		public:
			inline SystemThread(Thread& thread) : tid(0), handle(INVALID_HANDLE_VALUE)
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

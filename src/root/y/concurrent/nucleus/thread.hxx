namespace Yttrium
{
    namespace Concurrent
    {
        SystemThread * Nucleus:: acquireSystemThread(Thread &thread)
        {
            assert(data);
            assert(code);
            return data->threads.produce(thread);
        }

        void Nucleus:: releaseSystemThread(SystemThread * const st) noexcept
        {
            assert(data);
            assert(code);
            assert(st);
            data->threads.recycle(st);
        }


    }

}


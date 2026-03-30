
namespace Yttrium
{
    namespace Concurrent
    {
        SystemCondition * Nucleus:: acquireSystemCondition()
        {
            assert(data);
            return data->conditions.produce();
        }

        void Nucleus:: releaseSystemCondition(SystemCondition * const cond) noexcept
        {
            assert(cond);
            assert(data);
            data->conditions.recycle(cond);
        }

    }

}

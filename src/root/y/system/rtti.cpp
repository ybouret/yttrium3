#include "y/system/rtti.hpp"
#include "y/exception.hpp"

namespace Yttrium
{

    const char * const RTTI:: CallSign = "RTTI";
    

    RTTI:: Alias:: Alias(const String & id) :
    String(id),
    next(0)
    {
    }
    

    RTTI:: Alias:: ~Alias() noexcept
    {
        
    }


    RTTI:: RTTI(const String &uuid) :
    CountedObject(),
    pool()
    {
        Coerce(pool).store( new Alias(uuid) );
    }

    RTTI:: ~RTTI() noexcept
    {

    }

    bool RTTI:: is(const String &uid) const noexcept
    {
        for(const Alias *alias=pool.head;alias;alias=alias->next)
        {
            if(*alias == uid) return true;
        }
        return false;
    }

    const String & RTTI :: name() const noexcept
    {
        assert(pool.size>0);
        return *pool.head;
    }

    const char * RTTI:: callSign() const noexcept
    {
        return name().c_str();
    }

#if 0
    RTTI & RTTI:: aka(const char * const id)
    {
        const String uid = id;
        if(!is(uid))
            Coerce(pool).store( new Alias( uid.c_str() ) );
        
        return *this;
    }
#endif

    std::ostream & operator<<(std::ostream &os, const RTTI &rtti)
    {
        const RTTI::Alias *alias = rtti.pool.head;
        assert(alias);
        os << '[' << *alias;
        for(alias=alias->next;alias;alias=alias->next)
            os << ',' << *alias;
        return os << ']';
    }


}

#include "y/pointer/arc.hpp"
#include "y/container/associative/hash/map.hpp"
#include "y/singleton.hpp"

namespace Yttrium
{

    namespace
    {
        typedef ArcPtr<RTTI>          HRTTI;
        typedef HashMap<String,HRTTI> HMap;

    }

    class RTTI:: Table :
    public Singleton<Table,ClassLockPolicy>,
    public HMap
    {
    public:
        static const char * const CallSign;
        static const Longevity    LifeTime = 0;


        inline explicit Table() :
        Singleton<Table, ClassLockPolicy>(),
        HMap()
        {
        }

        inline virtual ~Table() noexcept {}

        RTTI & get(const String &uid)
        {
            Y_Lock(access);

            // search existing
            {
                HRTTI * const hook = search(uid);
                if(hook) return **hook;
            }

            // create new
            HRTTI handle = new RTTI(uid);
            if(!insert(uid,handle))
                throw Specific::Exception(CallSign,"uexpected multiple <%s>", uid.c_str());
            return *handle;
        }

        inline bool has(const RTTI &rtti) const noexcept
        {
            for(const Alias *alias=rtti.pool.head;alias;alias=alias->next)
            {
                const HRTTI * const hook = search(*alias);
                if(!hook)              continue; // mismatch name
                if( &**hook != &rtti ) continue; // mismatch address
            }
            return false;
        }

        RTTI & aka(RTTI &rtti, const String &uid)
        {
            //------------------------------------------------------------------
            //
            // sanity check
            //
            //------------------------------------------------------------------
            assert(has(rtti));

            //------------------------------------------------------------------
            //
            // check is work is needed
            //
            //------------------------------------------------------------------
            if(rtti.is(uid))
                return rtti; // already named

            //------------------------------------------------------------------
            //
            // check is uid is un use
            //
            //------------------------------------------------------------------
            {
                const HRTTI * const hook = search(uid);
                if(hook) throw Specific::Exception(CallSign,"<%s> is already in use", uid.c_str());
            }

            //------------------------------------------------------------------
            //
            // store new alias
            //
            //------------------------------------------------------------------
            Coerce(rtti.pool).store( new Alias(uid) );

            try
            {
                // TODO
                rtti;
            }
            catch(...)
            {
                delete Coerce(rtti.pool).query();
                throw;
            }

            return rtti;
        }


    private:
        Y_Disable_Copy_And_Assign(Table);
        friend class Singleton<Table,ClassLockPolicy>;
    };


    const char * const RTTI:: Table:: CallSign = "RTTI:: Table";

}

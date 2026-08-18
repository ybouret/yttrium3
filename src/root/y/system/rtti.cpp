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
#include "y/concurrent/life-time.hpp"

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
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;
        static const Longevity    LifeTime = LifeTimeFor::RTTI;


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit Table() :
        Singleton<Table, ClassLockPolicy>(),
        HMap()
        {
        }

        inline virtual ~Table() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! on-the-fly get/create
        RTTI & get(const String &uid)
        {
            Y_Lock(access);

            //__________________________________________________________________
            //
            // search existing
            //___________________________________________________________________
            {
                HRTTI * const hook = search(uid);
                if(hook) return **hook;
            }

            //__________________________________________________________________
            //
            // create new
            //__________________________________________________________________
            HRTTI handle = new RTTI(uid);
            if(!insert(uid,handle))
                throw Specific::Exception(CallSign,"uexpected multiple <%s>", uid.c_str());

            RTTI & rtti = *handle; assert(has(rtti));
            return rtti;
        }

        //! check ownership
        inline bool has(const RTTI &rtti) const noexcept
        {
            for(const Alias *alias=rtti.pool.head;alias;alias=alias->next)
            {
                const HRTTI * const hook = search(*alias);
                if(!hook)              continue; // mismatch name
                if( &**hook != &rtti ) continue; // mismatch address
                return true;
            }
            return false;
        }

        //! create an alias for 
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
            {
                assert( search(uid) );
                return rtti; // already named
            }

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

            //------------------------------------------------------------------
            //
            // register alias
            //
            //------------------------------------------------------------------
            try
            {
                const HRTTI handle = &rtti;
                if(!insert(uid,handle))
                    throw Specific::Exception(CallSign,"failed to insert <%s> for <%s>", uid.c_str(), rtti.name().c_str());
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


    RTTI & RTTI:: aka(const String &uid)
    {
        static Table &table = Table::Instance();
        return table.aka(*this,uid);
    }

    RTTI & RTTI:: aka(const char * const uid)
    {
        const String _(uid);
        return aka(_);
    }

    RTTI & RTTI:: Of(const std::type_info &ti)
    {
        static Table &table = Table::Instance();
        const String  uid   = ti.name();
        return table.get(uid);
    }

}

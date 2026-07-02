#include "y/rtld/dll.hpp"
#include "y/system/exception.hpp"
#include "y/type/destroy.hpp"
#include "y/ability/lockable.hpp"

#if defined(Y_BSD)
#include <dlfcn.h>
#define Y_DLL_HANDLE void *
#define Y_DLL_CLOSE() dlclose(handle)
#endif

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define Y_DLL_HANDLE HMODULE
#define Y_DLL_CLOSE() ::FreeLibrary(handle)
#endif // defined(Y_WIN)

namespace Yttrium
{

    class DLL:: Code : public CountedObject
    {
    public:

        template <typename NAME> inline
        explicit Code(const NAME &path) :
        soname(path),
        handle( Open(soname) )
        {
            withhold();
        }


        inline virtual ~Code() noexcept
        {
            assert(handle);
            Y_Giant_Lock();
            Y_DLL_CLOSE();
            Coerce(handle) = 0;
        }

        const String       soname;
        Y_DLL_HANDLE const handle;
    private:
        Y_Disable_Copy_And_Assign(Code);

        static inline
        Y_DLL_HANDLE Open(const String &path)
        {
            Y_Giant_Lock();
            const char * const name = path.c_str();
#if defined(Y_BSD)
            (void) dlerror();
            void * const h = dlopen(name,RTLD_LAZY);
            if(!h)
                throw Specific::Exception("dlopen", "<%s> for '%s'", dlerror(), name);
            return h;
#endif // defined(Y_BSD)

        }


    };

#define Y_DLL_CTOR(INIT) code( INIT ), name(code->soname)

    DLL:: DLL(const String &     path) : Y_DLL_CTOR( new Code(path) ) {}

    DLL:: DLL(const char * const path) : Y_DLL_CTOR( new Code(path) ) {}

    DLL:: DLL(const DLL &dll) noexcept :
    CountedObject(),
    Y_DLL_CTOR( dll.code )
    { code->withhold();     }

    DLL:: ~DLL() noexcept
    {
        assert(code);
        if(code->liberate())
            Destroy(code);
    }


}

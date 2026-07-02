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

        inline virtual ~Code() noexcept
        {
            assert(handle);
            Y_Giant_Lock();
            Y_DLL_CLOSE();
            Coerce(handle) = 0;
        }

    private:
        Y_Disable_Copy_And_Assign(Code);
        Y_DLL_HANDLE const handle;
    };




    DLL:: ~DLL() noexcept
    {

        assert(code);
        if(code->liberate())
        {
            Destroy(code);
        }
    }


}

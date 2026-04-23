#include "y/counting/permutation.hpp"
#include "y/exception.hpp"
#include "y/memory/troop.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/counting/c/perm.h"
#include "y/type/destroy.hpp"

namespace Yttrium
{

    apn Permutation:: Cardinal(const size_t n)
    {
        return apn::Factorial(n);
    }

    const char * const Permutation::CallSign = "Permutation";

    const char * Permutation:: callSign() const noexcept { return CallSign; }

    static inline Cardinality getCard(const size_t n)
    {
        if(n<1) throw Specific::Exception(Permutation::CallSign,"n<1");
        const apn np = Permutation::Cardinal(n);
        return np.cast<Cardinality>(Permutation::CallSign,0);
    }

    class Permutation:: Code : public Memory::Troop<size_t,Object>
    {
    public:
        typedef Memory::Troop<size_t,Object> CodeMemory;

        inline explicit Code(const size_t n) :
        CodeMemory(n),
        perm()
        {
            Coerce(size) = n;
            Y_Perm_Init(&perm,n);
            Y_Perm_Boot(&perm,cxx);
        }


        inline virtual ~Code() noexcept
        {
            Coerce(size) = 0;
        }

        inline void boot() noexcept { Y_Perm_Boot(&perm,cxx); }
        inline bool next() noexcept { return 0 != Y_Perm_Next(&perm,cxx); }


        Y_Perm         perm;

    private:
        Y_Disable_Copy_And_Assign(Code);
    };

    Permutation:: Permutation(const size_t n) :
    Schedule( getCard(n)  ),
    code( new Code(n) )
    {
    }

    Permutation:: ~Permutation() noexcept
    {
        assert(0!=code);
        Destroy(code);
    }

    void Permutation:: doBoot() noexcept
    {
        code->boot();
    }

    bool Permutation:: doNext() noexcept
    {
        return code->next();
    }


    size_t Permutation:: size() const noexcept
    {
        return code->perm.n;
    }

    size_t Permutation:: capacity() const noexcept
    {
        return code->perm.n;
    }

    const size_t & Permutation:: ask(const size_t i) const noexcept
    {
        assert(i>0);
        assert(i<=code->perm.n);
        return code->cxx[i];
    }



}

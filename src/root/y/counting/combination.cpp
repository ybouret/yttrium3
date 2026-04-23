
#include "y/counting/combination.hpp"
#include "y/exception.hpp"
#include "y/memory/troop/legacy.hpp"
#include "y/counting/c/comb.h"

namespace Yttrium
{


    apn Combination:: Cardinal(const size_t n, const size_t k)
    {
        assert(n>0);
        assert(k>0);
        assert(k<=n);
        return apn::Comb(n,k);
    }

    const char * const Combination::CallSign = "Combination";

    const char   * Combination:: callSign() const noexcept { return CallSign; }


    static inline Cardinality getCard(const size_t n, const size_t k)
    {
        if(n<1)   throw Specific::Exception(Combination::CallSign,"n<1");
        if(k<1)   throw Specific::Exception(Combination::CallSign,"k<1");
        if(k>n)   throw Specific::Exception(Combination::CallSign,"k>n");

        const apn np = Combination::Cardinal(n,k);
        return np.cast<Cardinality>(Combination::CallSign,0);
    }

    class Combination:: Code : public Memory::LegacyTroop<size_t,Object>
    {
    public:
        typedef Memory::LegacyTroop<size_t,Object> CodeMemory;

        inline explicit Code(const size_t n,
                             const size_t k) :
        CodeMemory(k),
        comb()
        {
            Y_Comb_Init(&comb,n,k);
            Y_Comb_Boot(&comb,cxx);
        }


        inline virtual ~Code() noexcept {}

        inline void boot() noexcept { Y_Comb_Boot(&comb,cxx); }
        inline bool next() noexcept { return 0 != Y_Comb_Next(&comb,cxx); }

        Y_Comb         comb;

    private:
        Y_Disable_Copy_And_Assign(Code);
    };

    Combination:: Combination(const size_t n, const size_t k) :
    Schedule( getCard(n,k)  ),
    code( new Code(n,k) )
    {
    }

    Combination:: ~Combination() noexcept
    {
        assert(0!=code);
        delete code;
        code = 0;
    }

    void Combination:: doBoot() noexcept
    {
        code->boot();
    }

    bool Combination:: doNext() noexcept
    {
        return code->next();
    }


    size_t Combination:: size() const noexcept
    {
        return code->comb.k;
    }

    size_t Combination:: capacity() const noexcept
    {
        return code->comb.k;
    }

    const size_t & Combination:: ask(const size_t i) const noexcept
    {
        assert(i>0);
        assert(i<=code->comb.k);
        return code->cxx[i];
    }

    
}

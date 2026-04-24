
#include "y/apex/n/code.hpp"
#include "y/type/destroy.hpp"
#include "y/swap.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const       Natural:: CallSign = "apn";
        const char *             Natural:: callSign() const noexcept { return CallSign; }
        const Natural::Directly_ Natural:: Directly = {};

        Natural:: Natural() : code( new KegType() )
        {
        }

        Natural:: Natural(const Directly_ &, void * const handle) noexcept :
        code( handle )
        {
            assert(code);
        }

        Natural:: Natural(const natural_t n) : code( new KegType(CopyOf,n) )
        {
        }

        Natural:: Natural(const TwoToThePowerOf_ &_, const size_t n) : code( new KegType(_,n) )
        {
        }

        Natural:: Natural(Random::CoinFlip &coin, const size_t n) : code ( KegType::MakeRandom(coin,n) )
        {
        }


        Natural:: ~Natural() noexcept
        {
            assert(code);
            delete (KegType *)code;
            Coerce(code) = 0;
        }

        Natural:: Natural(const Natural &n) :
        Number(),
        code( new KegType( *static_cast<const KegType *>(n.code) ) )
        {
        }
        
        Natural & Natural:: operator=( const Natural & n )
        {
            assert(code);
            void * temp = new KegType( *static_cast<const KegType *>(n.code) );
            delete (KegType *)code;
            Coerce(code) = temp;
            return *this;
        }

        Natural & Natural:: operator=( const natural_t n )
        {
            assert(code);
            static_cast<KegType *>(code)->assign(n);
            return *this;
        }

        Natural & Natural:: xch(Natural &n) noexcept
        {
            assert(code);
            assert(n.code);
            CoerceSwap(code,n.code);
            return *this;
        }

        String Natural:: toHex() const
        {
            return static_cast<const KegType *>(code)->toHex();
        }

        String Natural:: toBin() const
        {
            return static_cast<const KegType *>(code)->toBin();
        }

        std::ostream & operator<<(std::ostream &os, const Natural &n)
        {
            if( 0 != (os.flags() & std::ios_base::hex) )
                return os << n.toHex();
            else
                return os << n.toDec();
        }

        natural_t Natural:: lsw() const noexcept
        {
            return static_cast<const KegType *>(code)->getNatural();
        }

        void Natural:: ldz() noexcept
        {
            static_cast<KegType *>(code)->ldz();
        }

        bool Natural:: is0() const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->bits <= 0;
        }


        bool Natural:: is1() const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->bits == 1;
        }

        bool Natural:: isOdd() const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->isOdd();
        }

        bool Natural:: isEven() const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->isEven();
        }

    }

}


#include "y/container/matrix/metrics.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"
#include <cassert>
#include "y/swap.hpp"

namespace Yttrium
{

    const char * const MatrixMetrics:: CallSign = "Matrix";


    void MatrixMetrics:: clear() noexcept
    {
        Coerce(rows)  = 0;
        Coerce(cols)  = 0;
        Coerce(items) = 0;
    }

    MatrixMetrics:: ~MatrixMetrics() noexcept
    {
        clear();
    }

    MatrixMetrics:: MatrixMetrics(const size_t nr, const size_t nc) :
    rows(nr),
    cols(nc),
    items(rows*cols)
    {
        if( (rows<=0 && cols>0) || (cols<=0 && rows>0) )
            throw Specific::Exception(CallSign,"invalid rows=%s and cols=%s", Decimal(rows).c_str(), Decimal(cols).c_str() );
    }

    MatrixMetrics:: MatrixMetrics(const MatrixMetrics &other) noexcept :
    rows(  other.rows  ),
    cols(  other.cols  ),
    items( other.items )
    {
    }

    MatrixMetrics:: MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &other) noexcept :
    rows(  other.cols  ),
    cols(  other.rows  ),
    items( other.items )
    {
    }

    void MatrixMetrics:: trade(MatrixMetrics &other) noexcept
    {
        CoerceSwap(rows,other.cols);
        CoerceSwap(rows,other.cols);
        CoerceSwap(items,other.items);
    }


}

#include "y/object/factory.hpp"
#include "y/container/matrix/row.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{

    void * MatrixMetrics:: acquireWorkspace(const size_t  bytesPerItem,
                                            size_t      & length,
                                            size_t      & offset)
    {

        assert(0==length);
        assert(0==offset);
        if(items<=0)
            return 0;
        else
        {
            static Memory::Allocator & factory     = Object::Factory:: Instance();
            static const size_t        bytesPerRow = sizeof( MatrixRow<int> );
            const size_t               rBytes       = Alignment::SystemMemory::Ceil( rows  * bytesPerRow  );
            const size_t               iBytes       = Alignment::SystemMemory::Ceil( items * bytesPerItem );
            void * const addr = factory.acquire(length = rBytes + iBytes);
            offset = rBytes;
            return addr;
        }
    }

    void MatrixMetrics:: releaseWorkspace(void * &addr, size_t &length) noexcept
    {
        if(addr)
        {
            assert(length>0);
            static Memory::Allocator & factory     = Object::Factory:: Location();
            factory.release(addr,length);
        }
        else
        {
            assert(0==length);
        }
    }



}

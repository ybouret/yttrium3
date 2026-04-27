
//! \file

#ifndef Y_MatrixMetrics_Included
#define Y_MatrixMetrics_Included 1

#include "y/config/setup.hpp"
#include "y/mkl/transpose-of.hpp"

namespace Yttrium
{

    class MatrixMetrics
    {
    public:
        static const char * const CallSign; //!< "Matrix"

        explicit MatrixMetrics(const size_t nr, const size_t nc);
        virtual ~MatrixMetrics() noexcept; //!< cleanup
        MatrixMetrics(const MatrixMetrics &) noexcept;
        explicit MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &) noexcept;

        void * acquireWorkspace(const size_t bytesPerItem,
                                size_t      &length,
                                size_t      &offset);

        void releaseWorkspace(void * &addr, size_t &length) noexcept;

        


        const size_t rows;
        const size_t cols;
        const size_t items;

    protected:
        void trade(MatrixMetrics &) noexcept;
        void clear() noexcept;

    private:
        Y_Disable_Assign(MatrixMetrics);
    };


}

#endif // !Y_MatrixMetrics_Included


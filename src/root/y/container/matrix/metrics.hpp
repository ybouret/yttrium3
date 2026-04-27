
//! \file

#ifndef Y_MatrixMetrics_Included
#define Y_MatrixMetrics_Included 1

#include "y/config/setup.hpp"
#include "y/mkl/transpose-of.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Metrics for Matrix
    //
    //
    //__________________________________________________________________________
    class MatrixMetrics
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign; //!< "Matrix"

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup with compatible rows and columns
        /**
         \param nr rows
         \param nc columns
         */
        explicit MatrixMetrics(const size_t nr, const size_t nc);
        virtual ~MatrixMetrics()                                   noexcept; //!< cleanup
        MatrixMetrics(const MatrixMetrics &)                       noexcept; //!< duplicate
        MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &) noexcept; //!< duplicate transpose

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! anonymous memory allocation
        /**
         \param bytesPerItem size of each item
         \param length       allocated memory
         \param offset       data offset in memory
         \return memory for rows and data
         */
        void * acquireWorkspace(const size_t bytesPerItem,
                                size_t      &length,
                                size_t      &offset);

        //! anonymous memory dealllocation
        /**
         \param addr   allocated memory
         \param length allocated bytes
         */
        void releaseWorkspace(void * &addr, size_t &length) noexcept;

        
        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________

        const size_t rows;  //!< number of rows
        const size_t cols;  //!< number of colums
        const size_t items; //!< number of items

    protected:
        void trade(MatrixMetrics &) noexcept; //!< no-throw exchange row,cols,items
        void clear()                noexcept; //!< clear rows,cols,items

    private:
        Y_Disable_Assign(MatrixMetrics); //!< discarded
    };


}

#endif // !Y_MatrixMetrics_Included


//! \file

#ifndef Y_Matrix_Included
#define Y_Matrix_Included 1

#include "y/container/matrix/metrics.hpp"
#include "y/container/matrix/row.hpp"
#include "y/object.hpp"
#include "y/type/copy-of.hpp"
#include "y/swap.hpp"
#include "y/ability/releasable.hpp"
#include "y/hide.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! C++ matrix
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Matrix : public MatrixMetrics, public Releasable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);        //!< alias
        typedef MatrixRow<T> RowType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty matrix
        inline explicit Matrix() noexcept : MatrixMetrics(0,0), length(0), row(0)
        {
        }


        //! setup matrix with default constructor
        /**
         \param nr rows
         \param nc columns
         */
        inline explicit Matrix(const size_t nr, const size_t nc) :
        MatrixMetrics(nr,nc),
        length(0),
        row(0)
        {
            allocate();
        }

        //! duplicate \param m source matrix
        inline Matrix(const Matrix &m) :
        MatrixMetrics(m),
        Releasable(),
        length(0), row(0)
        {
            duplicate(m);
        }

        //! duplicate \param m compatible source matrix
        template <typename U>
        inline Matrix(const CopyOf_ &, const Matrix<U> &m) :
        MatrixMetrics(m),
        length(0), row(0)
        {
            duplicate(m);
        }


        //! duplicate transpose \param _ helper \param m source matrix
        template <typename U>
        inline Matrix(const TransposeOf_ &_, const Matrix<U> &m) :
        MatrixMetrics(_,m),
        length(0), row(0)
        {
            duplicateTranspose(m);
        }

        //! assign any metrics matrix \param m source matrix \return *this
        inline Matrix & operator=(const Matrix &m)
        {
            if(m.rows==rows && m.cols==cols)
                assign(m);
            else {
                Matrix tmp(CopyOf,m);
                return xch(tmp);
            }
        }

        //! assign any metrics matrix \param m source matrix \return *this
        template <typename U>
        inline Matrix & operator=(const Matrix<U> &m)
        {
            if(m.rows==rows && m.cols==cols)
                assign(m);
            else {
                Matrix tmp(CopyOf,m);
                return xch(tmp);
            }
        }

        inline virtual ~Matrix() noexcept { deallocate(); } //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void release() noexcept { deallocate(); }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! assign all items for same metrics \param m source matrix
        template <typename U> inline
        void assign( const Matrix<U> &m )
        {
            assert(cols==m.cols); assert(rows==m.rows);
            for(size_t i=rows;i>0;--i) {
                MatrixRow<T>        &tgt_i = (*this)[i];
                const MatrixRow<U>  &src_i = m[i];
                for(size_t j=cols;j>0;--j) tgt_i[j] = src_i[j];
            }
        }

        //! assign all items for transpose metrics \param m source matrix
        template <typename U> inline
        void assignTranspose( const Matrix<U> &m )
        {
            assert(cols==m.rows); assert(rows==m.cols);
            for(size_t i=rows;i>0;--i) {
                MatrixRow<T>        &tgt_i = (*this)[i];
                for(size_t j=cols;j>0;--j) tgt_i[j] = m[j][i];
            }
        }



        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! change size if necessary \param nr new rows \param nc new cols \return *this
        inline Matrix & make(const size_t nr, const size_t nc)
        {
            if(rows!=nr||cols!=nc)
            {
                Matrix M(nr,nc); return xch(M);
            }
            else
                return *this;
        }

        //! Julia display \param os output \return os
        inline std::ostream & print(std::ostream &os) const
        {
            const Matrix &m = *this;
            if(rows<=0||cols<=0) {
                return os << "[]";
            }
            else {
                const bool has1D = rows==1 || cols==1;
                if(has1D) os << "hcat(";
                os << '[';
                m[1].print(os);
                for(size_t r=2;r<=rows;++r) m[r].print(os << ';');
                os << ']';
                if(has1D) os << ")";
                return os;
            }
        }

        //! C++ display
        inline friend std::ostream & operator<<(std::ostream &os, const Matrix &m)
        {
            return m.print(os);
        }


        //! access row \param irow row index \return irow-th row
        inline RowType & operator[](const size_t irow) noexcept
        {
            assert(irow<=rows);
            assert(irow>=1);
            assert(row);
            return row[irow];
        }

        //! access const row \param irow row index \return irow-th row
        inline const RowType & operator[](const size_t irow) const noexcept
        {
            assert(irow<=rows);
            assert(irow>=1);
            assert(row);
            return row[irow];
        }


        //! no throw exchange \param other another matrix \return *this
        inline Matrix & xch( Matrix &other ) noexcept
        {
            trade(other);
            Swap(length,other.length);
            CoerceSwap(row,other.row);
            return *this;
        }

        //! swap rows \param i first row \param j second row
        inline void swapRows(const size_t i, const size_t j) noexcept
        {
            assert(i>=1); assert(i<=rows);
            assert(j>=1); assert(j<=rows);
            Yttrium_BSwap(&row[i][1],&row[j][1],cols*sizeof(T));
        }

        //! swap columns \param i first column \param j second column
        inline void swapCols(const size_t i, const size_t j) noexcept
        {
            assert(i>=1); assert(i<=cols);
            assert(j>=1); assert(j<=cols);
            for(size_t r=rows;r>0;--r)
                Yttrium_BSwap(&row[r][i],&row[r][j],sizeof(T));
        }


        //! extract mino \param m target \param I excluded row \param J excluded column
        template <typename U>
        inline void minor(Matrix<U> &m, const size_t I, const size_t J) const
        {
            assert(m.rows+1==rows);
            assert(m.cols+1==cols);
            const size_t nr = rows;
            size_t       ir = 1;
            for(size_t i=1;   i<I;   ++i,++ir) copyMinorRow(m,ir,i,J);
            for(size_t i=I+1; i<=nr; ++i,++ir) copyMinorRow(m,ir,i,J);
        }

        //! in place multiplication: target = *this * source \param target output vector \param source input vector
        template <typename TARGET, typename SOURCE> inline
        void mul(TARGET &target, SOURCE &source) const
        {
            assert(rows==target.size()); assert(cols==source.size());
            Cameo::Addition<T> xadd(cols);
            for(size_t i=rows;i>0;--i)
                target[i] = xadd.dot( row[i], source);
        }

        //! in place multiplication and subtraction : target = *this * source - rhs
        /**
         \param target output vector
         \param source input vector
         \param rhs    vector to subtract
         */
        template <typename TARGET, typename SOURCE, typename RHS> inline
        void mulsub(TARGET &target, SOURCE &source, RHS &rhs) const
        {
            assert(rows==target.size());
            assert(cols==source.size());
            assert(rows==rhs.size());
            Cameo::Addition<T> xadd(cols);
            for(size_t i=rows;i>0;--i)
                target[i] = xadd.dotsub( row[i], source, rhs[i]);
        }

        //! *this = lhs * rhs \param lhs matrix \param rhs matrix
        template <typename LHS, typename RHS> inline
        void mmul(LHS &lhs, RHS &rhs)
        {
            assert(lhs.rows==rows);
            assert(rhs.cols==cols);
            assert(lhs.cols==rhs.rows);
            Matrix &           self = *this;
            const size_t       nr   = rows;
            const size_t       nc   = cols;
            const size_t       nx   = lhs.cols;
            Cameo::Addition<T> xadd(nx);
            for(size_t i=nr;i>0;--i)
            {
                for(size_t j=nc;j>0;--j)
                {
                    xadd.ldz();
                    for(size_t k=nx;k>0;--k)
                        xadd.addProd(lhs[i][k], rhs[k][j]);
                    self[i][j] = xadd();
                }
            }
        }

        //! *this = lhs * rhs' \param lhs matrix \param rhs matrix
        template <typename LHS, typename RHS> inline
        void mmul(LHS &lhs, const TransposeOf_ &, RHS &rhs)
        {
            assert(rows==lhs.rows);
            assert(cols==rhs.rows);
            assert(lhs.cols==rhs.cols);
            Matrix &           self = *this;
            const size_t       nr   = rows;
            const size_t       nc   = cols;
            Cameo::Addition<T> xadd(lhs.cols);
            for(size_t i=nr;i>0;--i)
            {
                for(size_t j=nc;j>0;--j)
                    self[i][j] = xadd.dot(lhs[i],rhs[j]);
            }
        }

        //! *this = lhs' * rhs \param lhs matrix \param rhs matrix
        template <typename LHS, typename RHS> inline
        void mmul(const TransposeOf_ &, LHS &lhs, RHS &rhs)
        {
            assert(rows==lhs.cols);
            assert(cols==rhs.cols);
            assert(lhs.rows==rhs.rows);
            Matrix &           self = *this;
            const size_t       nr   = rows;
            const size_t       nc   = cols;
            const size_t       nx   = lhs.rows;
            Cameo::Addition<T> xadd(nx);
            for(size_t i=nr;i>0;--i)
            {
                for(size_t j=nc;j>0;--j)
                {
                    xadd.ldz();
                    for(size_t k=nx;k>0;--k)
                        xadd.addProd(lhs[k][i],rhs[k][j]);
                    self[i][j] = xadd();
                }
            }
        }

        //! compute Gram matrix \param P to compute P'*P
        template <typename MATRIX> inline
        void gram(MATRIX &P)
        {
            assert(P.rows==rows);
            assert(P.rows==cols);
            Matrix &           self = *this;
            const size_t       nr   = rows;
            Cameo::Addition<T> xadd(P.cols);
            for(size_t i=1;i<=nr;++i)
            {
                self[i][i] = xadd.dot(P[i],P[i]);
                for(size_t j=i+1;j<=nr;++j)
                    self[i][j] = self[j][i] = xadd.dot(P[i],P[j]);
            }
        }





    private:
        size_t              length; //!< bytes
        RowType * const     row;    //!< row in [1:rows]

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        template <typename U> inline
        void copyMinorRow(Matrix<U> &m, const size_t ir, const size_t i, const size_t J) const
        {
            assert(i>=1); assert(i<=rows);
            MatrixRow<U>       & mrow = m[ir];
            const MatrixRow<T> & self = row[i];
            const size_t         nc   = cols;
            size_t               jr   = 1;
            for(size_t j=1;   j<J;   ++j,++jr) mrow[jr] = self[j];
            for(size_t j=J+1; j<=nc; ++j,++jr) mrow[jr] = self[j];
        }

        inline void allocate()
        {
            if(items<=0) return;
            size_t offset = 0;
            void * entry  = acquireWorkspace( sizeof(T), length, offset);
            assert(offset>=rows*sizeof(RowType));
            try {
                Coerce(row) = createRows(entry,createData( static_cast<char *>(entry) + offset ));
            }
            catch(...) { releaseWorkspace(entry,length); throw; }
        }

        inline RowType * createRows(void * const entry, MutableType * data) noexcept
        {
            RowType * const target = static_cast<RowType *>(entry);
            {
                RowType * r = target;
                for(size_t i=rows;i>0;--i,data += cols)
                    new (r++) RowType(data,cols);
            }
            return target-1;
        }

        inline MutableType * createData(void * const addr)
        {
            size_t              built = 0;
            MutableType * const data  = static_cast<MutableType *>(addr);
            try
            {
                while(built<items)
                {
                    new (data+built) MutableType();
                    ++built;
                }
            }
            catch(...)
            {
                while(built-- > 0)
                    Destruct(data+built);
                throw;
            }
            assert(items==built);
            return data;
        }

        template <typename U>
        inline MutableType * copyData(void * const addr, const Matrix<U> &m )
        {
            assert(rows==m.rows);
            assert(cols==m.cols);
            size_t              built = 0;
            MutableType * const data  = static_cast<MutableType *>(addr);
            try
            {
                for(size_t i=1;i<=rows;++i)
                {
                    const MatrixRow<U> &m_i = m[i];
                    for(size_t j=1;j<=cols;++j)
                    {
                        new (data+built) MutableType(m_i[j]);
                        ++built;
                    }
                }
            }
            catch(...)
            {
                while(built-- > 0)
                    Destruct(data+built);
                throw;
            }
            return data;
        }

        template <typename U>
        inline void duplicate( const Matrix<U> &m )
        {
            if(items<=0) return;
            size_t offset = 0;
            void * entry  = acquireWorkspace( sizeof(T), length, offset);
            try
            {
                Coerce(row) = createRows(entry,copyData( (static_cast<char *>(entry) + offset ), m) );
            }
            catch(...) { releaseWorkspace(entry,length); throw; }
        }


        template <typename U>
        inline MutableType * copyTransposeData(void * const addr, const Matrix<U> &m )
        {
            assert(rows==m.cols);
            assert(cols==m.rows);
            size_t              built = 0;
            MutableType * const data  = static_cast<MutableType *>(addr);
            try
            {
                for(size_t i=1;i<=rows;++i)
                {
                    for(size_t j=1;j<=cols;++j)
                    {
                        new (data+built) MutableType(m[j][i]);
                        ++built;
                    }
                }
            }
            catch(...)
            {
                while(built-- > 0)
                    Destruct(data+built);
                throw;
            }
            return data;
        }

        template <typename U>
        inline void duplicateTranspose( const Matrix<U> &m )
        {
            if(items<=0) return;
            size_t offset = 0;
            void * entry  = acquireWorkspace( sizeof(T), length, offset);
            try
            {
                Coerce(row) = createRows(entry,copyTransposeData( (static_cast<char *>(entry) + offset ), m) );
            }
            catch(...) { releaseWorkspace(entry,length); throw; }
        }


        inline void deallocate() noexcept
        {
            if(items)
            {
                assert(length>0); assert(row);
                for(size_t i=rows;i>0;--i) Destruct(row+i);
                releaseWorkspace( *(void **)(&++Coerce(row)),length);
                assert(0==length);
                assert(0==row);
                clear();
            }
            else
            {
                assert(0==row);
                assert(0==length);
                assert(0==cols);
                assert(0==rows);
            }
        }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

    };

}

#endif // !Y_Matrix_Included


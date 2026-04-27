//! \file

#ifndef Y_Matrix_Included
#define Y_Matrix_Included 1

#include "y/container/matrix/metrics.hpp"
#include "y/container/matrix/row.hpp"
#include "y/object.hpp"
#include "y/type/copy-of.hpp"
#include "y/swap.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    template <typename T>
    class Matrix : public MatrixMetrics, public Releasable
    {
    public:
        Y_Args_Expose(T,Type);
        typedef MatrixRow<T> RowType;

        inline explicit Matrix() noexcept : MatrixMetrics(0,0), length(0), row(0)
        {
        }


        inline explicit Matrix(const size_t nr, const size_t nc) :
        MatrixMetrics(nr,nc),
        length(0),
        row(0)
        {
            allocate();
        }

        inline Matrix(const Matrix &m) :
        MatrixMetrics(m),
        Releasable(),
        length(0), row(0)
        {
            duplicate(m);
        }

        template <typename U>
        inline Matrix(const CopyOf_ &, const Matrix<U> &m) :
        MatrixMetrics(m),
        length(0), row(0)
        {
            duplicate(m);
        }


        template <typename U>
        inline Matrix(const TransposeOf_ &_, const Matrix<U> &m) :
        MatrixMetrics(_,m),
        length(0), row(0)
        {
            duplicateTranspose(m);
        }



        //! assign all item or same metrics
        template <typename U> inline
        void assign( const Matrix<U> &m )
        {
            assert(cols==m.cols); assert(rows==m.rows);
            for(size_t i=rows;i>0;--i)
            {
                MatrixRow<T>        &tgt_i = (*this)[i];
                const MatrixRow<U>  &src_i = m[i];
                for(size_t j=cols;j>0;--j) tgt_i[j] = src_i[j];
            }
        }

        //! assign all item or same metrics
        template <typename U> inline
        void assignTranspose( const Matrix<U> &m )
        {
            assert(cols==m.rows); assert(rows==m.cols);
            for(size_t i=rows;i>0;--i)
            {
                MatrixRow<T>        &tgt_i = (*this)[i];
                for(size_t j=cols;j>0;--j) tgt_i[j] = m[j][i];
            }
        }




        inline Matrix & operator=(const Matrix &m)
        {
            if(m.rows==rows && m.cols==cols)
                assign(m);
            else
            {
                Matrix tmp(CopyOf,m);
                return xch(tmp);
            }
        }

        template <typename U>
        inline Matrix & operator=(const Matrix<U> &m)
        {
            if(m.rows==rows && m.cols==cols)
                assign(m);
            else
            {
                Matrix tmp(CopyOf,m);
                return xch(tmp);
            }
        }


        inline virtual ~Matrix() noexcept
        {
            deallocate();
        }


        // Interface
        inline virtual void release() noexcept { deallocate(); }


        // Methods
        inline std::ostream & print(std::ostream &os) const
        {
            const Matrix &m = *this;
            switch(rows+cols)
            {
                case 0: return os << "[]";
                case 2: assert(1==rows); assert(1==cols); return os << "hcat(" << m[1][1] << ")";
                default:
                    break;
            }
            assert(rows+cols>2);
            assert(rows>=1);
            m[1].print(os);
            for(size_t r=2;r<=rows;++r) m[r].print(os << ';');
            return os;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Matrix &m)
        {
            return m.print(os);
        }


        inline RowType & operator[](const size_t irow) noexcept
        {
            assert(irow<=rows);
            assert(irow>=1);
            assert(row);
            return row[irow];
        }


        inline const RowType & operator[](const size_t irow) const noexcept
        {
            assert(irow<=rows);
            assert(irow>=1);
            assert(row);
            return row[irow];
        }


        inline Matrix & xch( Matrix &other ) noexcept
        {
            trade(other);
            Swap(length,other.length);
            CoerceSwap(row,other.row);
            return *this;
        }

    private:
        size_t              length;
        RowType * const     row;

        inline void allocate()
        {
            if(items<=0) return;
            size_t offset = 0;
            void * entry  = acquireWorkspace( sizeof(T), length, offset);
            assert(offset>=rows*sizeof(RowType));
            try
            {
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
                    new (data+built) MutableType( (T)(built+1) );
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


    };

}

#endif // !Y_Matrix_Included


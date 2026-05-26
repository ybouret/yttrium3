
//! \file

#ifndef Y_Coven_Compress_Included
#define Y_Coven_Compress_Included 1

#include "y/coven/univocal.hpp"
#include "y/container/matrix.hpp"
#include "y/handy/basic/heavy/list.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //! Prepare input matrix for optimal processing
        //
        //______________________________________________________________________
        struct Compress
        {
            //! Compress mode
            enum  Mode
            {
                Transpose, //!< compress transpose of source matrix
                Duplicate  //!< compress duplicate of source matrix
            };

            //! count non zero items \param a input \return count of non zero items
            static size_t CountNonZeroIn(const Readable<apz> &a) noexcept;


            //! compress to univocal (not nul) uniq vectors
            /**
             \param target target matrix, empty upon failure
             \param source source matrix
             \param mode   compression mode
             \param nmin   minimal number of non zero coefficients
             \return true if target is not empty
             */
            template <typename T> static inline
            bool Build(Matrix<apz>        &target,
                       const Matrix<T>    &source,
                       const  Mode         mode,
                       const size_t        nmin = 0)

            {
                typedef Handy::BasicHeavyList<size_t> List;
                typedef List::NodeType                Node;
                if(source.rows<=0) { target.release(); return false; }

                //--------------------------------------------------------------
                //
                // prepare data
                //
                //--------------------------------------------------------------
                Matrix<apz>  output;
                switch(mode)
                {
                    case Duplicate: output.make(source.rows,source.cols); output.assign(source); break;
                    case Transpose: output.make(source.cols,source.rows); output.assignTranspose(source); break;
                }

                //--------------------------------------------------------------
                //
                // Study each row
                //
                //--------------------------------------------------------------
                const size_t n = output.rows;
                List         ok;
                for(size_t i=1;i<=n;++i)
                {
                    MatrixRow<apz> &out = output[i];
                    if(!Univocal::Make(out))             continue; // empty row
                    if(nmin>1&&CountNonZeroIn(out)<nmin) continue; // no enough data
                    bool keep = true;
                    for(size_t j=1;j<i;++j)
                    {
                        if(  out == output[j] ) {
                            keep = false;
                            break;
                        }
                    }
                    if(keep) ok << i;
                }

                //--------------------------------------------------------------
                //
                // compile target with kept index(ices) and univocal row(s)
                //
                //--------------------------------------------------------------
                const size_t nr = ok->size; if(!nr) { target.release(); return false; }
                target.make(nr,output.cols);
                {
                    size_t i=1;
                    for(const Node *node=ok->head;node;node=node->next,++i)
                        target[i].load(output[**node]);
                }
                return true;
            }

        };




    }

}

#endif // !Y_Coven_Compress_Included


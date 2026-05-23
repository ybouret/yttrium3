
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

        enum CompressMode
        {
            CompressTranspose,
            CompressDuplicate
        };
        template <typename T>
        inline bool Compress(Matrix<apz>        &target,
                             const Matrix<T>    &source,
                             const CompressMode  mode)

        {
            typedef Handy::BasicHeavyList<size_t> List;
            typedef List::NodeType                Node;
            if(source.rows<=0) { target.release(); return false; }

            // prepare data
            Matrix<apz>  output;
            switch(mode)
            {
                case CompressDuplicate: output.make(source.rows,source.cols); output.assign(source); break;
                case CompressTranspose: output.make(source.cols,source.rows); output.assignTranspose(source); break;
            }

            const size_t n = output.rows;
            List         ok;

            // study each row
            for(size_t i=1;i<=n;++i)
            {
                if(!Univocal::Make(output[i])) continue;
                bool keep = true;
                for(size_t j=1;j<i;++j)
                {
                    if( output[i] == output[j] ) {
                        keep = false;
                        break;
                    }
                }
                if(keep) ok << i;
            }

            std::cerr << "output=" << output << std::endl;
            std::cerr << "ok=" << ok << std::endl;
            const size_t nr = ok->size; if(!nr) { target.release(); return false; }

            target.make(nr,output.cols);
            {
                size_t i=1;
                for(const Node *node=ok->head;node;node=node->next,++i)
                    target[i].ld( output[**node] );
            }
            return true;
        }

    }

}

#endif // !Y_Coven_Compress_Included


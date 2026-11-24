//! \file

#ifndef Y_MKL_Fit_WriteXY_Included
#define Y_MKL_Fit_WriteXY_Included 1

#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            //__________________________________________________________________
            //
            //
            //
            //! Helper to save sample content
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            struct WriteXY
            {
                //! assuming ORDINATE is same as/vector of ABSCISSA
                static const size_t DIMENSIONS = sizeof(ORDINATE)/sizeof(ABSCISSA);

                //! emit DIMENSIONS values
                /**
                 \param fp output stream
                 \param y  ordinate(s)
                 */
                static inline void Emit(OutputStream &fp, const ORDINATE &y)
                {
                    const ABSCISSA * const p = (const ABSCISSA *) &y;
                    for(size_t i=0;i<DIMENSIONS;++i)
                        fp(" %.15g", (double) p[i]);
                }

                //! emit abscissae/ordinates/fits
                /**
                 \param fp output stream
                 \param x  abscissa
                 \param y  ordinate
                 \param yf fit ordinate
                 \param tag I/O tag
                 */
                static inline void To(OutputStream   &fp,
                                      const ABSCISSA &x,
                                      const ORDINATE &y,
                                      const ORDINATE &yf,
                                      const size_t    tag)
                {
                    fp("%.15g",(double)x);
                    Emit(fp,y);
                    Emit(fp,yf);
                    if(tag)
                        fp(" %s",Decimal(tag).c_str());
                    fp << '\n';
                }

            };


        }

    }

}

#endif // !Y_MKL_Fit_WriteXY_Included

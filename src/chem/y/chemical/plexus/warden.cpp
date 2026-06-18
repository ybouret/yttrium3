
#include "y/chemical/plexus/warden.hpp"
#include "y/counting/combination.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/apex/api/simplify.hpp"

#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Chemical
    {



        Warden:: ~Warden() noexcept
        {
        }

        Warden:: Warden(XML::Log &xml, const Conservations &canon)
        {
            const size_t Nc = canon.Nc;
            if(Nc>0)
            {
                typedef CountedMatrix<apz>     IPMatrix;
                typedef CountedMatrix<xreal_t> XPMatrix;
                Vector<IPMatrix::Pointer> ipm;
                Vector<XPMatrix::Pointer> xpm;

                const size_t rg = canon.rg;
                Y_XML_Element_Attr(xml,BuildWarden,Y_XML_Attr(rg));
                const size_t M    = canon.Qm.cols;
                size_t       count = 0;
                MKL::LU<apq> lu(rg);

                for(size_t k=1;k<=rg;++k)
                {
                    Combination  comb(Nc,k);
                    Matrix<apz>  alpha(k,M);
                    Matrix<apz>  alpha2(k,k);
                    Matrix<apz>  adjM(k,k);
                    Matrix<apz>  alpha3(k,M);
                    Matrix<apz>  proj(M,M);
                    size_t       numOK = 0;
                    do
                    {
                        for(size_t i=1;i<=k;++i)
                        {
                            alpha[i].load( canon.Qm[comb[i]] );
                        }
                        
                        if(k!=MKL::Rank::Of(alpha))
                        {
                            //Y_XMLog(xml, "[-]" << comb);
                            continue;
                        }
                        else
                        {
                            //Y_XMLog(xml, "[+]" << comb);
                            ++numOK;
                            ++count;

                            alpha2.gram(alpha); assert(k==MKL::Rank::Of(alpha2));
                            const apz detM = lu.determinant(alpha2);
                            lu.adjoint(adjM,alpha2);
                            alpha3.mmul(adjM,alpha);
                            proj.mmul(TransposeOf,alpha,alpha3);

                            for(size_t i=1;i<=M;++i)
                            {
                                for(size_t j=1;j<i;++j)    Sign::MakeOpposite( Coerce(proj[i][j].s) );
                                for(size_t j=i+1;j<=M;++j) Sign::MakeOpposite( Coerce(proj[i][j].s) );
                                proj[i][i] = detM - proj[i][i];
                            }
                            Apex::Simplify::Matrix(proj,detM);
                            //std::cerr << "comb=" << comb << "=> proj   = " << proj << "/" << detM << std::endl;

                            assert(ipm.size()==xpm.size());

                            size_t I = 0;
                            for(size_t i=ipm.size();i>0;--i)
                            {
                                const IPMatrix &ip = *ipm[i];
                                if(ip.denom == detM && ip.isEqualTo(proj) )
                                {
                                    I = i;
                                    break;
                                }
                            }

                            if(I<=0)
                            {
                                // create new
                                const IPMatrix::Pointer itemp( new IPMatrix(proj,detM) );
                                const xreal_t           denom = detM.cast<int>("projection","denominator");
                                XPMatrix::Pointer       xtemp( new XPMatrix(M,M,denom) );
                                for(size_t i=M;i>0;--i)
                                {
                                    for(size_t j=M;j>0;--j)
                                    {
                                        (*xtemp)[i][j] = (xreal_t) (*itemp)[i][j].cast<int>("projection","coefficient");
                                    }
                                }
                            }




                        }
                    } while( comb.next() );
                    Y_XMLog(xml, "rank = " << std::setw(3) << k << " => " << std::setw(5) << numOK << " cells");
                }

                Y_XMLog(xml, "possible cells: " << count);
            }

        }
        
    }

}

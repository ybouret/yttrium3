
#include "y/chemical/plexus/warden.hpp"
#include "y/counting/combination.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/apex/api/simplify.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Warden:: Cell:: Cell(const Readable<size_t> & _key,
                             const Matrix<apz>      & _mat) :
        key(CopyOf,_key),
        next(0),
        prev(0)
        {
        }

        Warden:: Cell:: ~Cell() noexcept
        {
        }


        Warden:: ~Warden() noexcept
        {
        }

        Warden:: Warden(XML::Log &xml, const Canon &canon) :
        cells(canon.rg)
        {
            const size_t Nc = canon.Nc;
            if(Nc>0)
            {
                const size_t rg = canon.rg;
                Y_XML_Element_Attr(xml,BuildWarden,Y_XML_Attr(rg));
                const size_t M    = canon.Qm.cols;
                size_t       count = 0;
                MKL::LU<apq> lu(rg);

                for(size_t k=1;k<=rg;++k)
                {
                    Cell::List & clst = cells[k];
                    Combination  comb(Nc,k);
                    Matrix<apz>  alpha(k,M);
                    Matrix<apz>  alpha2(k,k);
                    Matrix<apz>  adjM(k,k);
                    Matrix<apz>  alpha3(k,M);
                    Matrix<apz>  alpha4(M,M);
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
                            //std::cerr << "alpha =" << alpha << std::endl;
                            //std::cerr << "alpha2=" << alpha2 << std::endl;
                            const apz detM = lu.determinant(alpha2);
                            lu.adjoint(adjM,alpha2);
                            //std::cerr << "adjM = " << adjM << std::endl;
                            //std::cerr << "detM = " << detM << std::endl;
                            alpha3.mmul(adjM,alpha);
                            //std::cerr << "alpha3 = " << alpha3 << std::endl;
                            alpha4.mmul(TransposeOf,alpha,alpha3);
                            //std::cerr << "alpha4 = " << alpha4 << " , detM=" << detM << std::endl;

                            for(size_t i=1;i<=M;++i)
                            {
                                for(size_t j=1;j<i;++j)    Sign::MakeOpposite( Coerce(alpha4[i][j].s) );
                                for(size_t j=i+1;j<=M;++j) Sign::MakeOpposite( Coerce(alpha4[i][j].s) );
                                alpha4[i][i] = detM - alpha4[i][i];
                            }
                            //std::cerr << "proj   = " << alpha4 << " #/" << detM << std::endl;
                            //std::cerr << "comb=" << comb << "=> proj   = " << alpha4 << " #/" << detM << std::endl;
                            Apex::Simplify::Matrix(alpha4,detM);
                            std::cerr << "comb=" << comb << "=> proj   = " << alpha4 << " #/" << detM << std::endl;
                            
                        }
                    } while( comb.next() );
                    Y_XMLog(xml, "rank = " << std::setw(3) << k << " => " << std::setw(5) << numOK << " cells");
                }

                Y_XMLog(xml, "possible cells: " << count);
            }

        }
        
    }

}

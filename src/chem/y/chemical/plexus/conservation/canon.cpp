

#include "y/chemical/plexus/conservation/canon.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Canon:: ~Canon() noexcept
            {
            }

            Canon:: Canon(const Law &first) :
            Object(),
            species( new SpRoll() ),
            laws(),
            next(0),
            prev(0),
            lfmt()
            {
                laws.pushTail(first);
            }

            bool Canon:: accepts(const Law &law) const noexcept
            {
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                {
                    if( (**ln).linkedTo(law) ) return true;
                }
                return false;
            }


            void Canon:: compileSpecies()
            {
                species->free();
                lfmt.reset();
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                {
                    const Law &law = **ln;
                    lfmt.enroll(law);
                    for(const Actor *ac=law->head;ac;ac=ac->next)
                    {
                        species->inscribe(ac->sp);
                    }
                }
                Indexed::AuxLabel( Indexed::TopHSort( Coerce(species->list) ) );
            }

             

            

            void Canon:: compile(XML::Log &xml, const IMatrix &topNuT)
            {
                //--------------------------------------------------------------
                //
                //
                // finalize state
                //
                //
                //--------------------------------------------------------------
                const size_t cardinal = laws->size;
                Y_XML_Element_Attr(xml,CompileCanon, Y_XML_Attr(cardinal) );
                if(xml.verbose)
                {
                    for(const LNode *ln=laws->head;ln;ln=ln->next)
                    {
                        const Law &law = **ln;
                        lfmt.print(xml() << "[+] d_( ",law,Justify::Center) << " )=0" << std::endl;
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // create dedicated species list
                //
                //
                //--------------------------------------------------------------
                compileSpecies();
                Y_XMLog(xml, "[@] " << species->list);


                //--------------------------------------------------------------
                //
                //
                // compile each law
                //
                //
                //--------------------------------------------------------------
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                    Coerce( **ln ).compile(xml,species->list,topNuT);
            }


        }

    }

}

#if 0
#include "y/counting/combination.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/apex/api/simplify.hpp"
#include "y/chemical/type/ikey.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {

            class PMatrix : public CountedObject
            {
            public:
                typedef ArcPtr<PMatrix> Ptr;

                explicit PMatrix(const Matrix<apz> &Num,
                                 const apz         &Den) :
                CountedObject(),
                numer(Num),
                denom(Den)
                {
                }

                virtual ~PMatrix() noexcept
                {
                }

                const Matrix<apz> numer;
                const apz         denom;

            private:
                Y_Disable_Copy_And_Assign(PMatrix);
            };

            class GMatrix : public CountedObject
            {
            public:
                typedef Keyed<IKey, ArcPtr<GMatrix> > Ptr;
                typedef HashSet<IKey,Ptr>             Set;

                explicit GMatrix(const Readable<size_t> &k,
                                 const PMatrix::Ptr     &p) :
                comb(k),
                pmat(p)
                {
                }

                virtual ~GMatrix() noexcept {}

                const IKey & key() const noexcept { return comb; }

                const IKey          comb;
                const PMatrix::Ptr  pmat;


            private:
                Y_Disable_Copy_And_Assign(GMatrix);
            };

            class GSupply : public GMatrix::Set
            {
            public:
                explicit GSupply()  : GMatrix::Set()
                {

                }

                virtual ~GSupply() noexcept
                {
                }

                void push(const Readable<size_t> &k,
                          const PMatrix::Ptr     &p)
                {
                    const GMatrix::Ptr pgm = new GMatrix(k,p);
                    if(!insert(pgm))
                        throw Specific::Exception("Canon::Compile", "unexpected multiple combination detected!");
                }

                void push(const Readable<size_t> &k,
                          const Matrix<apz>      &numer,
                          const apz              &denom)
                {
                    const PMatrix::Ptr p = new PMatrix(numer,denom);
                    push(k,p);
                }


                const PMatrix::Ptr * query(const Matrix<apz> &numer,
                                           const apz         &denom) const noexcept
                {
                    for(ConstIterator it=begin();it!=end();++it)
                    {
                        const GMatrix      &gm = **it;
                        const PMatrix::Ptr &ppm = gm.pmat;
                        const PMatrix      &pm  = *ppm;
                        if(denom==pm.denom && pm.numer.isEqualTo(numer) )
                            return &ppm;
                    }
                    return 0;
                }

            private:
                Y_Disable_Copy_And_Assign(GSupply);

            };


            void Canon:: compileSolvers(XML::Log &xml)
            {

                const size_t Nc = Gamma.rows;
                const size_t M  = Gamma.cols;
                Y_XML_Element_Attr(xml,CompileSolvers, Y_XML_Attr(Nc)  << Y_XML_Attr(rg) );
                apn          nmax = 0;
                apn          nslv = 0;
                apn          nmat = 0;
                MKL::LU<apq> lu(rg);
                //GSupply      gdb;
                for(size_t rank=1;rank<=rg;++rank)
                {
                    Matrix<apz>  gamma(rank,M);
                    Matrix<apq>  ggt(rank,rank);
                    Combination  comb(Nc,rank);
                    const apn    ntry = comb.total;
                    Y_XML_Element_Attr(xml,Study,Y_XML_Attr(rank) << Y_XML_Attr(ntry) );
                    nmax += ntry;
                    do
                    {
                        // create sub matrix
                        for(size_t i=1;i<=rank;++i)
                        {
                            gamma[i].load( Gamma[ comb[i] ] );
                        }

                        ggt.gram(gamma);
                        std::cerr << "ggt=" << ggt << std::endl;

                        continue;

                        if( MKL::Rank::Of(gamma) < rank )
                        {
                            Y_XMLog(xml, "[-] " << comb);
                            continue;
                        }
                        else
                        {
                            ++nslv;
                            std::cerr << "[+] " << comb << std::endl;
                        }

#if 0
                        ggt.gram(gamma);
                        denom = lu.determinant(ggt);  assert(!denom.is0());
                        lu.adjoint(adj,ggt);
                        ag.mmul(adj,gamma);
                        numer.mmul(TransposeOf,gamma,ag);
                        for(size_t i=1;i<=M;++i)
                        {
                            for(size_t j=1;j<=M;++j)
                            {
                                Sign::MakeOpposite( Coerce(numer[i][j].s) );
                            }
                            numer[i][i] += denom;
                        }
                        Apex::Simplify::Matrix(numer,denom);
#endif

#if 0
                        const PMatrix::Ptr * const pppm = gdb.query(numer,denom);
                        if(pppm)
                        {
                            gdb.push(comb,*pppm);
                        }
                        else
                        {
                            gdb.push(comb,numer,denom);
                            ++nmat;
                            Y_XMLog(xml,"proj=" << numer << "/" << denom);
                        }
#endif


                    }
                    while(comb.next());
                }
                Y_XMLog(xml, "-- Solvers::Maxi = " << nmax);
                Y_XMLog(xml, "-- Solvers::Kept = " << nslv);
                Y_XMLog(xml, "-- Solvers::Proj = " << nmat);


            }

        }

    }

}

#endif


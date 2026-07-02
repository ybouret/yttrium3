

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
            Gamma(),
            rg(0),
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

            void Canon:: compileMetrics()
            {
                const size_t Nc = laws->size; assert(Nc>0);
                const size_t M  = species->list->size;
                Gamma.make(Nc,M);
                size_t i = 1;
                for(const LNode *ln=laws->head;ln;ln=ln->next,++i)
                {
                    const Law &law = **ln;
                    for(const Actor *ac=law->head;ac;ac=ac->next)
                    {
                        ac->sp(Gamma[i],AuxLevel) = ac->nu;
                    }
                }
                rg = MKL::Rank::Of(Gamma);
            }


            void Canon:: compile(XML::Log &xml)
            {
                // finalize
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

                // create dedicated species list
                compileSpecies();
                Y_XMLog(xml, "[@] " << species->list);

                // create local metrics
                compileMetrics();
                Y_XMLog(xml, "    Gamma = " << Gamma);
                Y_XMLog(xml, "    rg    = " << rg);

                // and solvers
                compileSolvers(xml);



#if 0
                for(const LNode *ln=laws->head;ln;ln=ln->next)
                    Coerce( **ln ).compile(species->list);
#endif

            }


        }

    }

}

#include "y/counting/combination.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            void Canon:: compileSolvers(XML::Log &xml)
            {
                const size_t Nc = Gamma.rows;
                const size_t M  = Gamma.cols;
                Y_XML_Element_Attr(xml,CompileSolvers, Y_XML_Attr(Nc)  << Y_XML_Attr(rg) );
                apn          nmax = 0;
                apn          nslv = 0;
                for(size_t rank=1;rank<=rg;++rank)
                {
                    Matrix<apz>  gamma(rank,M);
                    Combination  comb(Nc,rank);
                    Y_XML_Element_Attr(xml,Study,Y_XML_Attr(rank) << Y_XML_Attr(comb.total) );
                    nmax += comb.total;
                    do
                    {
                        // create sub matrix
                        for(size_t i=1;i<=rank;++i)
                        {
                            gamma[i].load( Gamma[ comb[i] ] );
                        }
                        if( MKL::Rank::Of(gamma) < rank )
                        {
                            Y_XMLog(xml, "[-] " << comb);
                            continue;
                        }
                        else
                        {
                            //std::cerr << "[+] " << comb << " => " << gamma << std::endl;
                            ++nslv;
                        }
                    }
                    while(comb.next());
                }
                Y_XMLog(xml, "-- Kept " << nslv << " / " << nmax);


            }

        }

    }

}

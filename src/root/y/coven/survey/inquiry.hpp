
//! \file

#ifndef Y_Coven_Inquiry_Included
#define Y_Coven_Inquiry_Included 1

#include "y/coven/survey.hpp"
#include "y/coven/tribes.hpp"

namespace Yttrium
{

    namespace Coven
    {

        class InquiryCommon : public Proxy<const Survey>
        {
        public:
            static int Width;
            explicit InquiryCommon();
            virtual ~InquiryCommon() noexcept;

            void output(XML::Log &xml, const size_t nr) const;

            const apn generated;
        private:
            Y_Disable_Copy_And_Assign(InquiryCommon);
        };

        enum InquiryHint
        {
            InquiryExcludesInitial,
            InquiryIncludesInitial
        };

        template <typename SURVEY>
        class Inquiry :  public InquiryCommon
        {
        public:

            template <typename T> inline
            explicit Inquiry(const Matrix<T> & mu,
                             const InquiryHint hint,
                             const unsigned    strategy) :
            survey()
            {
                const size_t dimension = mu.cols;
                if(dimension>0)
                {
                    //__________________________________________________________
                    //
                    // prepare resources
                    //__________________________________________________________
                    const Metrics   metrics(dimension);
                    RCache          rc;
                    VCache          vc(metrics);

                    //__________________________________________________________
                    //
                    // prepare for initial tribes
                    //__________________________________________________________
                    Tribe::Callback proc = 0;
                    void * const    args = (void*) & locus();
                    switch(hint)
                    {
                        case InquiryExcludesInitial: break;
                        case InquiryIncludesInitial: proc = Survey::Callback;
                    }
                    Tribes tribes(mu,strategy,vc,rc,proc,args);
                    Coerce(generated) = tribes->size;

                    //__________________________________________________________
                    //
                    // prepare for other data and iterate
                    //__________________________________________________________
                    proc = Survey::Callback;
                    while(true)
                    {
                        const size_t gen = tribes.generate(mu,strategy,proc,args);
                        if(gen<=0) break;
                        Coerce(generated) += tribes->size;
                    }
                }
            }

            inline virtual ~Inquiry() noexcept {}




        private:
            SURVEY    survey;

            inline virtual const Survey & locus() const noexcept { return survey; }

        };

    }

}

#endif // !Y_Coven_Inquiry_Included


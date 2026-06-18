
//! \file

#ifndef Y_Coven_Inquiry_Included
#define Y_Coven_Inquiry_Included 1

#include "y/coven/survey.hpp"
#include "y/coven/tribes.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Common API for Inquiries
        //
        //
        //______________________________________________________________________
        class InquiryCommon : public Proxy<const Survey>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static int Width; //!< display width for output

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit InquiryCommon();           //!< setup
            virtual ~InquiryCommon() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! output statistics for num rows
            void output(XML::Log &, const size_t) const;

            //! send to parent survey
            void sendTo(Survey &) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const apn generated; //!< generated tribes during inquiry

        private:
            Y_Disable_Copy_And_Assign(InquiryCommon); //!< discarded
        };


        //______________________________________________________________________
        //
        //
        //
        //! Perform inquiry on matrix rows to produce parametric survey
        //
        //
        //______________________________________________________________________
        template <typename SURVEY>
        class Inquiry :  public InquiryCommon
        {
        public:

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup and perform inquiry
            /**
             \param mu       matrix of row vectors
             \param nmin     min ncof in each vector
             \param strategy optimization strategy
             */
            template <typename T> inline
            explicit Inquiry(const Matrix<T> & mu,
                             const size_t      nmin,
                             const unsigned    strategy) :
            survey(nmin)
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
                    Tribe::Callback const proc = Survey::Callback;
                    void * const          args = (void*) & locus();
                    Tribes tribes(mu,strategy,vc,rc,proc,args);
                    Coerce(generated) = tribes->size;

                    //__________________________________________________________
                    //
                    // prepare for other data and iterate
                    //__________________________________________________________
                    while(true)
                    {
                        const size_t gen = tribes.generate(mu,strategy,proc,args);
                        if(gen<=0) break;
                        Coerce(generated) += tribes->size;
                    }
                }
            }

            //! cleanup
            inline virtual ~Inquiry() noexcept {}


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            inline void sendTo(SURVEY &primary) noexcept
            {
                primary.fusion(survey);
            }

        private:
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            SURVEY    survey; //!< target survey

            inline virtual const Survey & locus() const noexcept { return survey; }
            Y_Disable_Copy_And_Assign(Inquiry); //!< discarded
        };

    }

}

#endif // !Y_Coven_Inquiry_Included


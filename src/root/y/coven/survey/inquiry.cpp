
#include "y/coven/survey/inquiry.hpp"
#include "y/format/percent.hpp"
#include <iomanip>

namespace Yttrium
{

    namespace Coven
    {
        int InquiryCommon:: Width = 8;

        InquiryCommon:: InquiryCommon() : generated()
        {
        }

        InquiryCommon:: ~InquiryCommon() noexcept
        {
        }


        void InquiryCommon:: output(XML::Log &xml, const size_t num_rows) const
        {
            Y_XML_Element_Attr(xml,CovenInquiry, Y_XML_Attr(num_rows) );
            const apn     predicted = Tribes::MaxGenerated(num_rows); assert(generated<=predicted);
            {
                Y_XMLog(xml, "generated = " << std::setw(Width) << generated);
                Y_XMLog(xml, "predicted = " << std::setw(Width) << predicted);
            }
            if(predicted.is0()) return;
            {
                const apn     gained  = predicted - generated;
                const String  percent = Percent::APGet(gained,predicted);
                Y_XMLog(xml, "gained    = " << std::setw(Width) << percent);
            }

            //std::cerr << "generated " << generated << " / " << maxGen << std::endl;
            const Survey &survey  = **this;
            {
                Y_XMLog(xml, "sampling  = " << std::setw(Width) << survey.sampling);
                Y_XMLog(xml, "recorded  = " << std::setw(Width) << survey->size);
            }
            if(survey.sampling)
            {
                const String percent = Percent::Get(survey->size,survey.sampling);
                Y_XMLog(xml, "strength  = " << std::setw(Width) << percent);
            }
        }
    }

}


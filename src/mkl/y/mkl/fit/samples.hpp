
//! \file

#ifndef Y_MKL_Fit_Samples_Included
#define Y_MKL_Fit_Samples_Included 1

#include "y/mkl/fit/sample/data.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            template <typename ABSCISSA, typename ORDINATE>
            class Samples :
            public Sample<ABSCISSA,ORDINATE>,
            public Proxy< SuffixSet<String, typename Sample<ABSCISSA,ORDINATE>::Pointer > >
            {
            public:
                typedef Sample<ABSCISSA,ORDINATE>          SampleType;
                typedef typename SampleType::Pointer       SamplePointer;
                typedef typename SampleType::FunctionType  FunctionType;
                typedef typename SampleType::AdditionType  AdditionType;

                typedef SuffixSet<String,SamplePointer>    SampleDB;
                typedef typename SampleDB::Iterator        Iterator;
                typedef typename SampleDB::ConstIterator   ConstIterator;
                typedef DataSample<ABSCISSA,ORDINATE>      DataSampleType;

                using SampleType::vars;

                template <typename NAME>
                inline explicit Samples(const NAME &name) :
                SampleType(name),
                Proxy<SampleDB>(),
                db()
                {
                }


                inline virtual ~Samples() noexcept {}


                virtual size_t cardinal() const noexcept
                {
                    size_t ns = 0;
                    for(ConstIterator it=db.begin();it != db.end();++it)
                        ns += (**it).cardinal();
                    return ns;
                }

                inline virtual void save(OutputStream &fp) const
                {
                    for(ConstIterator it=db.begin();it != db.end();++it)
                    {
                        (**it).save(fp);
                        fp << '\n';
                    }
                }


                template <typename NAME>
                inline SampleType & operator()(const NAME &           name,
                                               const ABSCISSA * const xa,
                                               const ORDINATE * const ya,
                                               const size_t           na)
                {
                    DataSampleType * const ds   = new DataSampleType(name,xa,ya,na);
                    {
                        const SamplePointer sp   = ds;
                        if(!db.insert(sp)) throw Specific::Exception(this->c_str(),"multiple '%s'", sp->c_str());
                    }
                    Coerce(ds->tag) = db.size();
                    return *ds;
                }


            private:
                Y_Disable_Copy_And_Assign(Samples);
                SampleDB db;

                inline virtual const SampleDB & locus() const noexcept { return db; }

                inline virtual void collectD2(AdditionType             &sumD2,
                                              FunctionType             &F,
                                              const Readable<ABSCISSA> &aorg)
                {
                    for(Iterator it=db.begin();it != db.end();++it)
                        (**it).collectD2(sumD2,F,aorg);
                }
            };

        }

    }

}


#endif // !Y_MKL_Fit_Samples_Included

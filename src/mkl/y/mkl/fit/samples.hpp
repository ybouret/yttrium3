
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
            //__________________________________________________________________
            //
            //
            //
            //! Set of Samples
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class Samples :
            public Sample<ABSCISSA,ORDINATE>,
            public Proxy< SuffixSet<String, typename Sample<ABSCISSA,ORDINATE>::Pointer > >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Probe<ABSCISSA>                     ProbeType;       //!< alias
                typedef Sample<ABSCISSA,ORDINATE>           SampleType;      //!< alias
                typedef typename SampleType::Pointer        SamplePointer;   //!< alias
                typedef typename SampleType::FunctionType   FunctionType;    //!< alias
                typedef typename SampleType::GradientType   GradientType;    //!< alias
                typedef typename SampleType::AdditionType   AdditionType;    //!< alias
                typedef typename SampleType::AdditionHandle AdditionHandle;  //!< alias

                typedef SuffixSet<String,SamplePointer>    SampleDB;       //!< alias
                typedef typename SampleDB::Iterator        Iterator;       //!< alias
                typedef typename SampleDB::ConstIterator   ConstIterator;  //!< alias
                typedef DataSample<ABSCISSA,ORDINATE>      DataSampleType; //!< alias

                using SampleType::vars;
                using SampleType::access;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param name compatible name
                template <typename NAME>
                inline explicit Samples(const NAME &name) :
                SampleType(name),
                Proxy<SampleDB>(),
                db()
                {
                }


                //! cleanup
                inline virtual ~Samples() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
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

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! helper to create a new data sample
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
                Y_Disable_Copy_And_Assign(Samples); //!< discard
                SampleDB db; //!< set

                inline virtual const SampleDB & locus() const noexcept { return db; }

                inline virtual
                void gatherD2(ProbeType                & probe,
                              FunctionType             & F,
                              const Readable<ABSCISSA> & aorg)
                {
                    Y_Lock(access);
                    for(Iterator it=db.begin();it != db.end();++it)
                    {
                        (**it).gatherD2(probe,F,aorg);
                    }
                }

                inline virtual
                void gatherD2(ProbeType                & probe,
                              GradientType             & G,
                              const Readable<ABSCISSA> & aorg,
                              const Readable<bool>     & used,
                              Writable<ORDINATE>       & dFda)
                {
                    Y_Lock(access);
                    for(Iterator it=db.begin();it != db.end();++it)
                    {
                        (**it).gatherD2(probe,G,aorg,used,dFda);
                    }
                }

            };

        }

    }

}


#endif // !Y_MKL_Fit_Samples_Included

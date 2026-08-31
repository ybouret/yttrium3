
#ifndef Y_Chemical_Plexus_Clusters_Included
#define Y_Chemical_Plexus_Clusters_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/chemical/reactive/equilibrium/partition.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Gathering clusters
        //
        //
        //______________________________________________________________________
        class Clusters : public Proxy<const Core::ListOf<Cluster> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param xml for output
             \param eqs initial equilibria, updated
             \param t0  initial time evaluation
             */
            explicit Clusters(XML::Log   &  xml,
                              Equilibria &  eqs,
                              const xreal_t t0 = 0);

            //! cleanup
            virtual ~Clusters() noexcept;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! update all constants \param t evaluation time
            void update(const xreal_t t);

            //! output graphViz code
            /**
             \param fp output stream
             \param gr grade to render
             \return fp
             */
            OutputStream & viz(OutputStream &fp, const size_t gr) const;

            //! render graphViz
            /**
             \param dotName graphivz file name
             \param gr      grade to render
             */
            void renderGraphViz(const String & dotName, const size_t gr) const;


            //! render graphViz
            /**
             \param baseName dotName = baseName + gr + ".dot"
             \param gr       grade to render
             */
            template <typename BASENAME> inline
            void render(const BASENAME &baseName, const size_t gr) const
            {
                String _ = baseName;
                renderGraphViz( MakeDotName(_,gr), gr );
            }

            //! render all grades \param baseName base name for all graphs
            template <typename BASENAME> inline
            void renderAll(const BASENAME &baseName) const {
                for(size_t gr=1;gr<=maxGrade;++gr)
                    render(baseName,gr);
            }



        private:
            Y_Disable_Copy_And_Assign(Clusters); //!< discarded
            Y_Proxy_Decl();                      //!< helper
            CxxListOf<Cluster> list;             //!< inner list
            Vector<xreal_t>    topK;             //!< top level constants

            //! \return name
            static const String & MakeDotName(String &, const size_t);

        public:
            const XReadable & K;        //!< top level constant
            const size_t      maxGrade; //!< maximal grade over clusters

        private:
            const Partition part;       //!< initial partition

        };
    }

}

#endif // !Y_Chemical_Plexus_Clusters_Included


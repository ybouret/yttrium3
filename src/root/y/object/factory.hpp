//! \file

#ifndef Y_Object_Factory_Included
#define Y_Object_Factory_Included 1

#include "y/object.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/memory/allocator.hpp"
#include "y/calculus/meta2.hpp"
#include "y/core/meta-max.hpp"

#include "y/memory/metrics.hpp"
#include "y/memory/small/arena/metrics.hpp"
#include "y/memory/plastic/forge/metrics.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //!  Metrics for Object::Factory
    //
    //
    //__________________________________________________________________________
    template <size_t MAX_SLIM_BYTES>
    class ObjectFactory
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const size_t   MaxSlimBytes = MAX_SLIM_BYTES;                                             //!< alias from parameter
        static const unsigned MaxSlimShift = MetaExactLog2<MaxSlimBytes>::Value;                         //!< enforce power of two
        static const size_t   MinNumBlocks = Memory::Small::ArenaMetrics::MinNumBlocks;                  //!< retrieve information
        static const size_t   MaxNumBlocks = Memory::Small::ArenaMetrics::MaxNumBlocks;                  //!< retrieve information
        static const size_t   DataLocation = Memory::Small::ArenaMetrics::DataLocation;                  //!< retrieve information
        static const size_t   NumPredicted = DataLocation + MinNumBlocks*MaxSlimBytes;                   //!< assumed bytes per Chunk
        static const size_t   MinRawLength = MetaMax<NumPredicted,Memory::Metrics::DefaultBytes>::Value; //!< adjusted bytes per Chunk
        static const size_t   MinUserBytes = MetaNextPowerOfTwo<MinRawLength>::Value;                    //!< rounded bytes per Chunk
        static const size_t   UserBlocks   = (MinUserBytes-DataLocation) / MaxSlimBytes;                 //!< fitting blocks in Chunk
        typedef typename Core::MetaAccept< (UserBlocks<=MaxNumBlocks) >::Type HasValidSlimBytes;         //!< alias
        static HasValidSlimBytes Check = 1;                                                              //!< checking possibler MAX_SLIM_BYTES
        static const size_t MaxFairBytes = MinUserBytes - Memory::Plastic::ForgeMetrics::ReservedSize;   //!< matching medium sized object limit
        static const size_t MaxVastBytes = Memory::Metrics::MaxPageBytes;                                //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit ObjectFactory() noexcept {} //!< setup
        inline virtual ~ObjectFactory() noexcept {} //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(ObjectFactory); //!< discarded
    };

    typedef ObjectFactory<256> ObjectFactoryType; //!< default factory type

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
    
    //__________________________________________________________________________
    //
    //
    //
    //!  Object::Factory gathers LEVEL-1 caches
    //
    //
    //__________________________________________________________________________
    class Object :: Factory :
    public Singleton<Factory,ClassLockPolicy>,
    public Memory::Allocator,
    public ObjectFactoryType
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;                              //!< "Object::Factory"
        static const Longevity    LifeTime = LifeTimeFor::ObjectFactory; //!< alias
        typedef ClassLockPolicy   Policy;                                //!< alias
        typedef void *            CompressType;                          //!< type to align Small::Blocks to
        
        //! named memory model
        enum Model
        {
            None, //!< NULL
            Slim, //!< uses Small
            Fair, //!< uses Pooled
            Vast  //!< uses Archon
        };

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! helper \param blockSize block size \return matching model
        static Model  ModelFor(const size_t blockSize)     noexcept;

        //! helper \param blockSize blockSize>0 \return aligned to CompressType
        static size_t SlimCompress(const size_t blockSize) noexcept;

        //! acquire with selected allocator w.r.t blockSize
        /**
         - blockSize = 0 => None => NULL
         - blockSize <= MaxSlimBytes => Small::Block[ SlimCompress(blockSize) ]
         - blockSize <= MaxFairBytes => Pooled (aligned on Plastic::Brick)
         - blockSize <= MaxVastBytes => Dyadic (aligned on NextPowerOfTwo)
         \param  blockSize required blockSize, 0 means NULL
         \return blockAddr
         */
        void * query(const size_t blockSize);

        //! release with selected allocator w.r.t blockSize
        /**
         \param blockAddr acquired block address
         \param blockSize required block size
         */
        void   store(void * const blockAddr, const size_t blockSize) noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! uses Small::Blocks,Pooled,Dyadic,Global
        /**
         \param blockSize required block size
         \return memory in selected allocator
         */
        virtual void * acquire(size_t &blockSize);

        //! used Small::Blocks,Pooled,Dyadic,Global
        /**
         \param blockAddr acquired memory
         \param blockSize required block size
         */
        virtual void   release(void * &blockAddr, size_t &blockSize) noexcept;

    private:
        friend class Singleton<Factory,Policy>;
        Y_Disable_Copy_And_Assign(Factory); //!< discarded
        explicit Factory();                 //!< setup
        virtual ~Factory() noexcept;        //!< cleanup
    };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

}


#endif // !Y_Object_Factory_Included



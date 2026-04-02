//! \file

#ifndef Y_Object_Factory_Included
#define Y_Object_Factory_Included 1

#include "y/object.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{

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
    public Memory::Allocator
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
        static const size_t       MaxSlimBytes;                          //!< limit to use Small::Blocks
        static const size_t       MaxFairBytes;                          //!< limit to use Memory::Pooled
        static const size_t       MaxVastBytes;                          //!< limit to use Memory::Archon

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



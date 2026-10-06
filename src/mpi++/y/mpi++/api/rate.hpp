//______________________________________________________________________________
//
//
//
//! Rate for statistics
//
//
//______________________________________________________________________________
class Rate
{
public:
    //__________________________________________________________________________
    //
    //
    // C++
    //
    //__________________________________________________________________________
    Rate()                         noexcept; //!< setup
    ~Rate()                        noexcept; //!< cleanup
    Rate(const Rate &)             noexcept; //!< duplicate
    Rate & operator=(const Rate &) noexcept; //!< assign \return *this

    //__________________________________________________________________________
    //
    //
    // Methods
    //
    //__________________________________________________________________________
    void          ldz()                      noexcept; //!< reset
    HumanReadable hrt(const System::WallTime &) const; //!< return readable rate
    String        str(const System::WallTime &) const; //!< return printable string

    //__________________________________________________________________________
    //
    //
    // Members
    //
    //__________________________________________________________________________
    uint64_t bytes; //!< cumulative bytes
    uint64_t ticks; //!< cumulative ticks
};

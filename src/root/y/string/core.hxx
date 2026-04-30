

template <> String<CH>:: ~String() noexcept
{
    Destroy(code);
}


//------------------------------------------------------------------------------
//
//
// Constructors
//
//
//------------------------------------------------------------------------------
template <> String<CH>:: String() : code( new Code( size_t(0) ) )
{
}


template <> String<CH>:: String(const String &s) :
Container(),
DynamicClass(),
SequenceType(),
Recyclable(),
Memory::ReadOnlyBuffer(),
Serializable(),
code( new Code(*s.code) )
{

}

template <> String<CH>:: String(const WithAtLeast_ &, const size_t n, const StringInit flag) :
DynamicClass(),
SequenceType(),
code( new Code(n) )
{
    switch(flag)
    {
        case InitBlankString: Coerce(code->size) = n; break;
        case InitEmptyString: break;
    }
}



template <> String<CH> & String<CH>:: operator=( const String &rhs )
{
    if( this != &rhs )
    {
        if(rhs.code->size<=code->capacity)
        {
            code->copy(rhs.code->entry,rhs.code->size);
        }
        else
        {
            Code * temp = new Code( *rhs.code );
            delete code;
            code = temp;
        }
    }
    return *this;
}

template <> String<CH> & String<CH>:: operator=( const CH C ) noexcept
{
    assert(code);
    code->clear();
    code->entry[0] = C;
    Coerce(code->size) = 1;
    assert(code->sanity());
    return *this;
}

template <> String<CH> & String<CH>:: operator=( const CH * const text )
{
    assert(code);
    const size_t tlen = StringLength(text);
    if(tlen<=code->capacity)
    {
        code->copy(text,tlen);
        assert(code->sanity());
    }
    else
    {
        Code * temp = new Code(text,tlen);
        delete code;
        code = temp;
    }
    return *this;
}




template <> String<CH>:: String(const CH * const text) :
DynamicClass(),
SequenceType(),
code( new Code(text) )
{
}


template <> String<CH>:: String(const CH * const buffer,
                                const size_t     buflen) :
DynamicClass(),
SequenceType(),
code( new Code(buffer,buflen) )
{
}


template <> String<CH>:: String(const CH C) :
DynamicClass(),
SequenceType(),
code( new Code(&C,1) )
{
}

//------------------------------------------------------------------------------
//
//
// Interface
//
//
//------------------------------------------------------------------------------
template <> size_t String<CH>:: size() const noexcept
{
    assert(code); return code->size;
}

template <> size_t String<CH>:: capacity() const noexcept
{
    assert(code); return code->capacity;
}

template <> String<CH>::ConstType & String<CH>:: ask(const size_t indx) const noexcept
{
    assert(code);
    assert(indx>0);
    assert(indx<=code->size);
    return code->cxx[indx];
}

template <> void String<CH>:: free() noexcept
{
    assert(code);
    return code->clear();
}

template <> void String<CH>:: popTail() noexcept
{
    assert(code);
    assert(code->size>0);
    code->trim(1);
}

template <> void String<CH>:: popHead() noexcept
{
    assert(code);
    assert(code->size>0);
    code->skip(1);
}

template <> const void * String<CH>:: ro() const noexcept
{
    assert(code);
    return code->entry;
}

template <> size_t String<CH>:: length() const noexcept
{
    assert(code);
    return code->size * sizeof(CH);
}

template <> size_t String<CH>:: serialize(OutputStream &fp) const 
{
    assert(code);
    size_t res = fp.vbr(code->size);
    for(size_t i=0;i<code->size;++i)
    {
        res += fp.cbr(code->entry[i]);
    }
    return res;
}



//------------------------------------------------------------------------------
//
//
// Methods
//
//
//------------------------------------------------------------------------------
template <> std::ostream & String<CH>:: print(std::ostream &os) const
{
    assert(code);
    return os << code->entry;
}

template <> String<CH> & String<CH>:: xch(String &other) noexcept
{
    Swap(code,other.code);
    return *this;
}

template <> const CH * String<CH>:: c_str() const noexcept
{
    assert(code);
    return code->entry;
}

//------------------------------------------------------------------------------
//
//
// addition constructor
//
//
//------------------------------------------------------------------------------
template <> String<CH> :: String(const CH * const lhs, const size_t lhsSize,
                                 const CH * const rhs, const size_t rhsSize) :
DynamicClass(),
SequenceType(),
code( new Code(lhsSize+rhsSize) )
{
    assert(!(0==lhs&&lhsSize>0));
    assert(!(0==rhs&&rhsSize>0));
    code->cat(lhs,lhsSize);
    code->cat(rhs,rhsSize);
}

//------------------------------------------------------------------------------
//
//
// Addition operators
//
//
//------------------------------------------------------------------------------
template <> String<CH> String<CH>:: Add(const String &lhs, const String &rhs)
{
    return String(lhs.code->entry,lhs.code->size,
                  rhs.code->entry,rhs.code->size);
}

template <> String<CH> String<CH>:: Add(const String &lhs, const CH * const rhs)
{
    return String(lhs.code->entry,lhs.code->size,
                  rhs,StringLength(rhs));
}

template <> String<CH> String<CH>:: Add(const CH * const lhs, const String &rhs)
{
    return String(lhs,StringLength(lhs),
                  rhs.code->entry,rhs.code->size);
}

template <> String<CH> String<CH>:: Add(const String &lhs, const CH C)
{
    return String(lhs.code->entry,lhs.code->size,
                  &C,1);
}

template <> String<CH> String<CH>:: Add(const CH C, const String &rhs)
{
    return String(&C,1,
                  rhs.code->entry,rhs.code->size);
}


//------------------------------------------------------------------------------
//
//
// in place additions
//
//
//------------------------------------------------------------------------------
template <> String<CH> & String<CH>:: operator+=( const CH C )
{
    if(code->size<code->capacity)
    {
        code->cat(&C,1);
        return *this;
    }
    else
    {
        String tmp = Add(*this,C);
        return xch(tmp);
    }
}

template <> String<CH> & String<CH>:: operator+=( const String &s )
{
    if(code->capacity-code->size>=s.code->size)
    {
        code->cat(s.code->entry,s.code->size);
        return *this;
    }
    else
    {
        String tmp = Add(*this,s);
        return xch(tmp);
    }
}


template <> String<CH> & String<CH>:: operator+=( const CH * const text )
{
    const size_t tlen = StringLength(text);
    if(code->capacity-code->size>=tlen)
    {
        code->cat(text,tlen);
        return *this;
    }
    else
    {
        String tmp = Add(*this,text);
        return xch(tmp);
    }
}


//------------------------------------------------------------------------------
//
//
// comparison
//
//
//------------------------------------------------------------------------------

namespace
{
    static inline SignType CompareStrings(const CH * lit, const size_t litSize,
                                          const CH * big) noexcept
    {
        for(size_t n=litSize;n>0;--n)
        {
            switch( Sign::Of(*lit,*big) )
            {
                case Negative: return Negative;
                case Positive: return Positive;
                case __Zero__: ++lit; ++big; continue;
            }
        }
        return Negative;
    }
}

template <> SignType String<CH>::Cmp(const CH * lhs, const size_t lhsSize,
                                     const CH * rhs, const size_t rhsSize) noexcept
{

    assert( !(0==lhs&&lhsSize>0) );
    assert( !(0==rhs&&rhsSize>0) );

    if(lhsSize<rhsSize)
    {
        return CompareStrings(lhs,lhsSize,rhs);
    }
    else
    {
        if( rhsSize<lhsSize )
            return Sign::Opposite( CompareStrings(rhs,rhsSize,lhs));
        else
        {
            assert(lhsSize==rhsSize);
            for(size_t n=lhsSize;n>0;--n)
            {
                switch( Sign::Of(*lhs,*rhs) )
                {
                    case Negative: return Negative;
                    case Positive: return Positive;
                    case __Zero__: ++lhs; ++rhs; continue;
                }
            }
            return __Zero__;
        }
    }


}


template <> SignType String<CH>:: Cmp(const String &lhs, const String &rhs) noexcept
{
    return Cmp(lhs.code->entry,lhs.code->size,
               rhs.code->entry,rhs.code->size);
}

template <> SignType String<CH>:: Cmp(const String &lhs, const CH * const rhs) noexcept
{
    return Cmp(lhs.code->entry,lhs.code->size,
               rhs,StringLength(rhs));
}

template <> SignType String<CH>:: Cmp(const CH * const lhs, const String &rhs) noexcept
{
    return Cmp(lhs,StringLength(lhs),
               rhs.code->entry,rhs.code->size);
}

template <> SignType String<CH>:: Cmp(const String &lhs, const CH C) noexcept
{
    return Cmp(lhs.code->entry,lhs.code->size,
               &C,1);
}

template <> SignType String<CH>:: Cmp(const CH C, const String &rhs) noexcept
{
    return Cmp(&C,1,
               rhs.code->entry,rhs.code->size);
}

//
template <> String<CH> & String<CH>:: reverse() noexcept
{
    code->reverse();
    return *this;
}

//------------------------------------------------------------------------------
//
//
// end of interface
//
//
//------------------------------------------------------------------------------
template <> void String<CH>::pushTail(ParamType c)
{
    assert(code);
    *this += c;
}



template <> void String<CH>::pushHead(ParamType c)
{
    assert(code);
    if(code->size<code->capacity)
    {
        code->pre(c);
    }
    else
    {
        String tmp = Add(c,*this);
       (void) xch(tmp);
    }
}

template <> String<CH>::ConstType & String<CH>:: getHead() const noexcept
{
    assert(code);
    assert(code->size>0);
    return code->entry[0];
}


template <> String<CH>::ConstType & String<CH>:: getTail() const noexcept
{
    assert(code);
    assert(code->size>0);
    return code->cxx[code->size];
}


template <> String<CH> String<CH>::Read(InputStream &fp, const char * const varName)
{
    const size_t nch = fp.vbr<size_t>(varName,"size"); 
    String<CH>   res(WithAtLeast,nch,InitEmptyString);

    for(size_t i=0;i<nch;++i)
        res += fp.cbr<CH>(varName,"char");
    return res;
}

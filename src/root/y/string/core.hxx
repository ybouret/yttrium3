
template <> String<CH>:: String() : code( new Code( size_t(0) ) )
{
}

template <> String<CH>:: ~String() noexcept
{
    Destroy(code);
}

template <> String<CH>:: String(const String &s) : BaseClass(), code( new Code(*s.code) )
{

}

template <> String<CH>:: String(const WithAtLeast_ &, const size_t n, const StringInit flag) :
BaseClass(), code( new Code(n) )
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
            code->copy( *rhs.code );
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
        memmove(code->entry,text,(Coerce(code->size)=tlen)*sizeof(CH));
        memset(code->entry+tlen,0,(code->capacity-tlen) * sizeof(CH));
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
BaseClass(), code( new Code(text) )
{
}


template <> String<CH>:: String(const CH * const buffer,
                                const size_t     buflen) :
BaseClass(),
code( new Code(buffer,buflen) )
{
}


template <> String<CH>:: String(const CH C) :
BaseClass(), code( new Code(&C,1) )
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

//------------------------------------------------------------------------------
//
//
// addition constructor
//
//
//------------------------------------------------------------------------------
template <> String<CH> :: String(const CH * const lhs, const size_t lhsSize,
                                 const CH * const rhs, const size_t rhsSize) :
BaseClass(), code( new Code(lhsSize+rhsSize) )
{
    assert(!(0==lhs&&lhsSize>0));
    assert(!(0==rhs&&rhsSize>0));
    code->cat(lhs,lhsSize);
    code->cat(rhs,rhsSize);
}

//------------------------------------------------------------------------------
//
//
// Additions
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


#if 0
//------------------------------------------------------------------------------
//
//
// in place equality
//
//
//------------------------------------------------------------------------------
template <> bool String<CH>:: AreEqual(const CH * lhs, const size_t lhsSize,
                                       const CH * rhs, const size_t rhsSize) noexcept
{
    assert(!(0==lhs&&lhsSize>0));
    assert(!(0==rhs&&rhsSize>0));
    if(lhsSize!=rhsSize) return false;
    for(size_t n=lhsSize;n>0;--n,++lhs,++rhs)
    {
        if(*lhs!=*rhs) return false;
    }
    return true;
}
#endif



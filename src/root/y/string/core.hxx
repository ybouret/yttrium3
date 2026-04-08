
template <> String<CH>:: String() : code( new Code() )
{
}

template <> String<CH>:: ~String() noexcept
{
    Destroy(code);
}

template <> String<CH>:: String(const String &s) :
code( new Code(*s.code) )
{

}


template <> String<CH> & String<CH>:: operator=( const String &rhs )
{
    if( this != &rhs )
    {
        if(rhs.code->size<=code->capacity)
        {
            code->steal( *rhs.code );
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

template <> const char * String<CH>:: c_str() const noexcept
{
    return GetLegacyString<CH>::From(code);
}


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
        
    }
    return *this;
}

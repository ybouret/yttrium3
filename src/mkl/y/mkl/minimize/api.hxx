

template <>
Minimize:: Engine<real_t>:: Engine() :
code( new Code() )
{
}

template <>
Minimize:: Engine<real_t>:: ~Engine() noexcept
{
    Destroy(code);
}

template <>
real_t Minimize:: Engine<real_t>:: find(XML::Log                & xml,
                                        const Process             proc,
                                        Triplet<real_t>         & x,
                                        Triplet<real_t>         & f,
                                        Function<real_t,real_t> & F,
                                        const Criterion           win)
{
    assert(code);
    return code->find(xml,proc,x,f,F,win);
}


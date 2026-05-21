
#include "y/jive/lexer.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Lexer:: ~Lexer() noexcept
        {
            psdb.release();
            (void)liberate();
        }

        void Lexer:: initialize()
        {
            const PScanner self(this);
            withhold();
            try
            {
                if(!psdb.insert(self))
                    throw Specific::Exception(name->c_str(),"failed to initialized database!!");
            }
            catch(...)
            {
                (void) liberate();
                throw;
            }
        }

       void  Lexer:: insert(Scanner * const scanner)
        {
           assert(scanner);
           assert(this!=scanner);
           const PScanner ps(scanner);
            if(!psdb.insert(ps))
                throw Specific::Exception(name->c_str(),"multiple record of '%s", ps->name->c_str());
       }

        void Lexer:: remove(const Identifier &id) noexcept
        {
            try { (void) psdb.remove(*id); } catch(...) {}
        }

        const Lexical::Rule & Lexer:: makeCall(Plugin &plugin)
        {
            try { return call(plugin.name,plugin.spark); }
            catch(...) { remove(plugin.name); throw; }
        }


        void Lexer:: unget(Lexeme * const lx) noexcept
        {
            assert(lx);
            lexemes.pushHead(lx);
        }

        Lexeme * Lexer:: get(Source &source)
        {
            assert(curr);
        GET:
            if(lexemes.size)
            {
                return lexemes.popHead();
            }
            else
            {
            PROBE:
                Lexical::Command cmd;
                Lexeme * const   lxm = curr->probe(source,cmd);
                if(lxm)
                {
                    return lxm;
                }
                else
                {
                    const char * const here = curr->name->c_str();
                    switch(cmd.kind)
                    {
                        case Lexical::Command::Quit:
                            std::cerr << "[EOS]" << std::endl;
                            switch(curr->onEOS)
                            {
                                case Lexical::AcceptEOS:
                                    return 0; // EOS
                                case Lexical::RejectEOS: {
                                    Specific::Exception excp(name->c_str(), "End Of Stream in <%s>", here);
                                    throw source->stamp(excp);
                                }
                            }
                            break;

                        case Lexical::Command::Call: {
                            assert(0!=cmd.args);
                            const String     id = *cmd.args; std::cerr << "call  to  <" << id << ">" << std::endl;
                            PScanner * const ps = psdb.search(id);
                            if(!ps)
                            {
                                Specific::Exception excp(name->c_str(),"<%s> got no <%s> to call", here, id.c_str());
                                throw source->stamp(excp);
                            }
                            history << *curr;
                            curr = & **ps;
                            if(Plugin * const plugin = dynamic_cast<Plugin *>(curr)) plugin->enter();

                        } goto PROBE;

                        case Lexical::Command::Back: {
                            assert(0==cmd.args);  std::cerr << "back from <" << curr->name << ">" << std::endl;
                            if(history->size<=0) {
                                Specific::Exception excp(name->c_str(),"no possible coming back from <%s>", here);
                                throw source->stamp(excp);
                            }
                            if(Plugin * const plugin = dynamic_cast<Plugin *>(curr)) plugin->leave();
                            curr = & history.tail(); history.popTail();
                        } goto GET;

                        default:
                            throw Exception("command not processed yet");
                    }

                    return 0;
                }
            }

        }



    }

}



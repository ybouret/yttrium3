
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
        
        
        
        void Lexer:: push(Lexeme * const lx) noexcept
        {
            assert(lx);
            lexemes.pushHead(lx);
        }
        
        const Lexical::Rule & Lexer:: makeCall(Plugin &plugin)
        {
            try { return call(plugin.name,plugin.expr); }
            catch(...) { remove(plugin.name); throw; }
        }
        


        Lexeme * Lexer:: pull(Source &source)
        {
            assert(0!=curr);

        PULL:
            //------------------------------------------------------------------
            //
            //
            //
            // top level get: cache or probe
            //
            //
            //
            //------------------------------------------------------------------
            if(lexemes.size)
            {
                //--------------------------------------------------------------
                //
                //
                // cache
                //
                //
                //--------------------------------------------------------------
                return lexemes.popHead();
            }
            else
            {
                //--------------------------------------------------------------
                //
                //
                // probe
                //
                //
                //--------------------------------------------------------------
            PROBE:
                Lexical::Command cmd;  assert(Lexical::Command::Quit==cmd.kind); assert(0==cmd.args);
                Lexeme * const   lxm = curr->probe(source,cmd);
                if(lxm)
                {
                    //----------------------------------------------------------
                    //
                    // found a regular lexeme
                    //
                    //----------------------------------------------------------
                    return lxm;
                }
                else
                {
                    //----------------------------------------------------------
                    //
                    // found a command lexeme
                    //
                    //----------------------------------------------------------
                    const char * const here = curr->name->c_str();
                    switch(cmd.kind)
                    {

                            //--------------------------------------------------
                        case Lexical::Command::Quit:
                            //--------------------------------------------------
                            switch(curr->onEOS)
                            {
                                case Lexical::AcceptEOS: break; // EOS: normal return
                                case Lexical::RejectEOS: {      // Illegal stop
                                    Specific::Exception excp(name->c_str(), "End Of Stream in <%s>", here);
                                    throw source->stamp(excp);
                                }
                            }
                            break; // ==> EOS

                            //--------------------------------------------------
                        case Lexical::Command::Call:
                        case Lexical::Command::Jump: { assert(0!=cmd.args);
                            //--------------------------------------------------
                            // search scanner to call
                            const String     id = *cmd.args; std::cerr << "call  to  <" << id << ">" << std::endl;
                            PScanner * const ps = psdb.search(id);
                            if(!ps) {
                                Specific::Exception excp(name->c_str(),"<%s> got no <%s> to call", here, id.c_str());
                                throw source->stamp(excp);
                            }

                            // modify current scanner, and history if that's a call
                            if(Lexical::Command::Call == cmd.kind) history << *curr;
                            curr = & **ps;
                        } goto PROBE; // still no lexeme

                            //--------------------------------------------------
                        case Lexical::Command::Back: { assert(0==cmd.args);
                            //--------------------------------------------------
                             std::cerr << "back from <" << curr->name << ">" << std::endl;
                            if(history->size<=0) {
                                Specific::Exception excp(name->c_str(),"no possible coming back from <%s>", here);
                                throw source->stamp(excp);
                            }
                            curr = & history.tail();
                            history.popTail();
                        } goto PULL; // may have created a lexeme
                    }

                    //----------------------------------------------------------
                    //
                    //
                    // valid EOS
                    //
                    //----------------------------------------------------------
                    return 0;

                }
            }

        }

#if 0
        Lexeme * Lexer:: get(Source &source)
        {
            assert(curr);
            //------------------------------------------------------------------
            //
            //
            // GET: test existing lexeme of probe...
            //
            //
            //------------------------------------------------------------------
        GET:
            if(lexemes.size)
            {
                return lexemes.popHead();
            }
            else
            {
                //--------------------------------------------------------------
                //
                //
                // PROBE: new lexeme
                //
                //
                //--------------------------------------------------------------
            PROBE:
                Lexical::Command cmd;
                Lexeme * const   lxm = curr->probe(source,cmd);
                if(lxm)
                {
                    //----------------------------------------------------------
                    //
                    // found a regular lexeme
                    //
                    //----------------------------------------------------------
                    return lxm;
                }
                else
                {
                    //----------------------------------------------------------
                    //
                    // found a command lexeme
                    //
                    //----------------------------------------------------------
                    const char * const here = curr->name->c_str();
                    switch(cmd.kind)
                    {
                            
                            //--------------------------------------------------
                        case Lexical::Command::Quit:
                            //--------------------------------------------------
                            switch(curr->onEOS)
                            {
                                case Lexical::AcceptEOS: return 0; // EOS: normal return
                                case Lexical::RejectEOS: {
                                    // illegal stop
                                    Specific::Exception excp(name->c_str(), "End Of Stream in <%s>", here);
                                    throw source->stamp(excp);
                                }
                            }
                            break;
                            
                            //--------------------------------------------------
                        case Lexical::Command::Call:
                        case Lexical::Command::Jump: {
                            //--------------------------------------------------
                            assert(0!=cmd.args);
                            // search scanner to call
                            const String     id = *cmd.args; std::cerr << "call  to  <" << id << ">" << std::endl;
                            PScanner * const ps = psdb.search(id);
                            if(!ps) {
                                Specific::Exception excp(name->c_str(),"<%s> got no <%s> to call", here, id.c_str());
                                throw source->stamp(excp);
                            }
                            
                            // modify history and current scanner
                            if(Lexical::Command::Call == cmd.kind) history << *curr;
                            curr = & **ps;
                        } goto PROBE; // still no lexeme
                            
                            //--------------------------------------------------
                        case Lexical::Command::Back: {
                            //--------------------------------------------------
                            assert(0==cmd.args);  std::cerr << "back from <" << curr->name << ">" << std::endl;
                            if(history->size<=0) {
                                Specific::Exception excp(name->c_str(),"no possible coming back from <%s>", here);
                                throw source->stamp(excp);
                            }
                            curr = & history.tail(); history.popTail();
                        } goto GET; // may have created a lexeme
                            
                    }
                    
                    return 0;
                }
            }
            
        }
#endif
        
    }
    
}



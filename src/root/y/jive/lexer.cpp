#include "y/jive/lexer.hpp"
#include "y/exception.hpp"
#include "y/jive/lexical/plugin/advanced.hpp"


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
        
        const Lexical::Rule & Lexer::makeDial(AdvancedPlugin &plugin)
        {
            try { return call(plugin.name,plugin.expr,&plugin, & AdvancedPlugin::onEnter); }
            catch(...) { remove(plugin.name); throw; }
        }


        void Lexer:: reset() noexcept
        {
            curr = this;
            history.free();
            lexemes.release();
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
                Y_Jive_Lexical(*lexemes.head << " (cached)");
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
                    Y_Jive_Lexical(*lxm);
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
                            Y_Jive_Lexical("[EOS]@" << source->str() );
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
                            const bool       jmp = (Lexical::Command::Jump == cmd.kind);
                            const String     id  = *cmd.args; 
                            PScanner * const ps  = psdb.search(id);
                            Y_Jive_Lexical(source->str() << (jmp? "jump" : "call") << ' ' << id);
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
                            Y_Jive_Lexical(source->str() << "done " << curr->name);
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



        
    }
    
}



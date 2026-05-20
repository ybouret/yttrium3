#include "y/jive/lexical/scanner/code.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Unit * Scanner:: get(Source &source, Command &command)
            {
                assert(code);

                //--------------------------------------------------------------
                //
                //
                // initialize according to source peek
                //
                //
                //--------------------------------------------------------------
                command.reset();
            LOOP:
                const Char * const     peek = source.peek(); if(!peek) return 0;
                const Spot             spot( static_cast<const Spot&>(*peek) );
                const uint8_t          byte = **peek;
                const MetaList * const prml = code->table.query(byte); // pointer to rules meta list
                if(!prml)
                {
                    const String        bad = source.guessInvalidString();
                    Specific::Exception excp(name->c_str(),"unexpected '%s'", bad.c_str());
                    throw spot.stamp(excp);
                }

                //--------------------------------------------------------------
                //
                //
                // scan list for best rule
                //
                //
                //--------------------------------------------------------------
                const MetaList &list = *prml; assert(list->size>0);
                std::cerr << "need to test #" << list->size<< " patterns" << std::endl;

                const Rule *    bestRule = 0;
                Token           bestData;
                const MetaNode * node = list->head;
                for(;node;node=node->next)
                {
                    const Rule &rule = **node;
                     std::cerr << "\t check '" << rule.name << "'" << std::endl;
                    if(rule.form->takes(bestData,source)) {
                        assert(bestData.size>0);
                        bestRule = &rule;
                        break;
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // unrecognized pattern
                //
                //
                //--------------------------------------------------------------
                if(!bestRule) {
                    assert(0==bestData.size);
                    const String        bad = source.guessInvalidString();
                    Specific::Exception excp(name->c_str(),"invalid '%s'", bad.c_str());
                    throw spot.stamp(excp);
                }

                //--------------------------------------------------------------
                //
                //
                // process remaining rules
                //
                //
                //--------------------------------------------------------------
                assert(bestData.size>0); // taken from source

                if(0!=(node=node->next))
                {
                    //----------------------------------------------------------
                    //
                    // restore source for remaining tests
                    //
                    //----------------------------------------------------------
                    source.uncpy(bestData);

                    for(;node;node=node->next)
                    {
                        const Rule &rule = **node;
                        Token       data;

                        std::cerr << "\t extra '" << rule.name << "'" << std::endl;
                        if(!rule.form->takes(data,source)) { assert(0==data.size); continue; } // no match
                        if(data.size<=bestData.size)       { source.unget(data);   continue; } // too small...


                        source.uncpy(data);         // restore source
                        bestData.swapForList(data); // new best data
                        bestRule = &rule;           // new best rule
                    }

                    //----------------------------------------------------------
                    //
                    // skip source from new bestData.size
                    //
                    //----------------------------------------------------------
                    assert(source.cached()>=bestData.size);
                    source.skip(bestData.size);
                }


                //--------------------------------------------------------------
                //
                //
                // process best rule
                //
                //
                //--------------------------------------------------------------
                std::cerr << "\t found '" << bestRule->name << "'" << std::endl;

                if( Rule::Endl & bestRule->deed ) source.endl();
                if( Rule::Drop & bestRule->deed ) goto LOOP;
                if( Rule::Emit & bestRule->deed )
                {
                    Unit * unit = new Unit(spot,bestRule->name);
                    unit->swapForList(bestData);
                    return unit;
                }

                return 0;
            }

        }

    }

}


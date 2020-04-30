//
// Created by bretzel on 20-04-20.
//

//#ifndef UTIL_LEXERTESTS_H
//#define UTIL_LEXERTESTS_H

#pragma once
#include <teacc/Diagnostics/Diagnostic.h>
#include <teacc/Lexer/LexicalScanners.h>


using namespace teacc::Lexer;



class LexerTests
{
public:
    static Expect<> Run(String::Collection Args_);
    
};


//#endif //UTIL_LEXERTESTS_H

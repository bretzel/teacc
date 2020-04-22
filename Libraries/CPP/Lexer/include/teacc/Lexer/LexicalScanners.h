//
// Created by bretzel on 20-04-22.
//

//#ifndef UTIL_LEXER_H
//#define UTIL_LEXER_H

#pragma once
#include <teacc/Lexer/Lib.h>
#include <teacc/Util/Rem.h>
#include <teacc/Lexer/TokenData.h>

namespace teacc
{
class LEXER_LIB LexicalScanners
{

    struct InternalCursor{
        const char* B = nullptr; ///> Absolute Beginning of the source text.
        const char* E = nullptr; ///> Absolute End of the soure text.
        const char* C = nullptr;
        
        bool operator ++();
        bool operator ++(int);
        bool SkipWS();
        bool Eof(const char* P=nullptr);
        int Index();
        int L = -1;
        int Col = -1;
        std::string ScanToEol();
        std::string Line();
        std::string Mark();
        std::string Location();
        bool _F = false;
        Util::Rem::Int ScanTo(const char *SubStr_);
    }_cursor;
    
    struct NumScanner
    {
        const char* B;
        const char* E;
        const char* C;
        const char* Eos;
        bool  Real = false;
        
        bool  Literal = true; ///< scan literal digits - do not validate hexadecimal...
        
        enum NumBase
        {
            None, Bin, Oct,Dec,Hex,/* ..., */ //  FUCK!!!
        }Num = None;

        enum State
        {
            Good, Bad
        }St_ = State::Bad;
        
        
        NumScanner() = default;
        NumScanner(const char* _c, const char* _eos);
        
        ~NumScanner() = default;
        
        //bool operator++();
        bool operator++(int);
        bool Ok(bool l);
        operator bool () { return (St_==Good) || (C>B); }
        State UpdateState();
        
        NumScanner::NumBase NumericBase();
        Type::T operator()();
    };

public:
    struct ConfigData
    {
        const char *mSource                          = nullptr;
        TokenData::Collection*  mTokensCollection    = nullptr;
    };
    
    using ReturnData = Util::Expect<LexicalScanners::ConfigData>;
    
    LexicalScanners()                       = default;
    LexicalScanners(const LexicalScanners&) = default;
    LexicalScanners(LexicalScanners&&)      = default;
    ~LexicalScanners();
    
    ConfigData& Config() { return mConfig; }
    
    
private:
    ConfigData mConfig;
    
};
}


//#endif //UTIL_LEXER_H

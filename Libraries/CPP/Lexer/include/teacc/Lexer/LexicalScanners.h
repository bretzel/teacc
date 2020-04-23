//
// Created by bretzel on 20-04-22.
//

//#ifndef UTIL_LEXER_H
//#define UTIL_LEXER_H

#pragma once
#include <teacc/Lexer/Lib.h>
#include <teacc/Util/Rem.h>
#include <teacc/Lexer/TokenData.h>

namespace teacc::Lexer
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
        void Sync();
        std::string ScanToEol();
        std::string Line();
        std::string Mark();
        std::string Location();
        bool _F = false;
        Util::Rem::Int ScanTo(const char *SubStr_);
        Util::Expect<std::string> ScanString();
        
        InternalCursor(const char* Source_);
    }mCursor;
    
    /*!
     * @brief Numeric litteral scanner.
     *
     * @note Bare scan as of the current version.
     */
    struct NumScanner
    {
        const char* B = nullptr;
        const char* E = nullptr;
        const char* C = nullptr;
        const char* Eos = nullptr;
        bool  Real = false;
        
        bool  Literal = true; ///< scan literal digits - do not validate hexadecimal...
        
        enum NumBase
        {
            None, Bin, Oct,Dec,Hex,/* ..., */ //  FUCK!!!
        }Num = None;

        
        NumScanner() = default;
        NumScanner(const char* _c, const char* _eos);
        
        ~NumScanner() = default;
        
        //bool operator++();
        bool operator++(int);

        explicit operator bool ();
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
    /*!
     * @brief nothing to do as of this version.
     */
    ~LexicalScanners()                      = default;
    
    ConfigData& Config() { return mConfig; }
    
    Util::Expect<std::size_t> Scan();
    
private:
    ConfigData mConfig;
    
    void Append(TokenData& Token_);
    
    #pragma region Scanners
    Util::Expect<> Number(TokenData&);
    Util::Expect<> Identifier(TokenData&);
    
    
    
};
}


//#endif //UTIL_LEXER_H

//
// Created by bretzel on 20-04-22.
//

//#ifndef UTIL_LEXER_H
//#define UTIL_LEXER_H

#pragma once
#include <teacc/Lexer/Lib.h>
#include <teacc/Util/Rem.h>
#include <teacc/Lexer/TokenData.h>
#include <libmng_types.h>

namespace teacc::Lexer
{
class LEXER_LIB Scanners
{

    struct InternalCursor{
        const char* B = nullptr; ///> Absolute Beginning of the source text.
        const char* E = nullptr; ///> Absolute End of the soure text.
        const char* C = nullptr;
        
        bool operator ++();
        bool operator ++(int);
        [[maybe_unused]] bool SkipWS();
        bool Eof(const char* P=nullptr) const;
        long Index() const;
        int L = -1;
        int Col = -1;
        void Sync();
        std::string ScanToEol();
        std::string Line() const;
        std::string Mark() const;
        std::string Location() const;
        bool _F = false;
        Util::Rem::Int ScanTo(const char *SubStr_);
        Util::Expect<std::string> ScanString();
        
        InternalCursor() = default;
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

        explicit operator bool () const;
        Type::T operator()() const;
    };

public:
    struct LEXER_LIB ConfigData
    {
        const char *mSource                          = nullptr;
        TokenData::Collection*  mTokensCollection    = nullptr;
    };
    
    
    using ReturnData = Util::Expect<Scanners::ConfigData>;
    using Return     = Util::Expect <> ;
    Scanners() = default;
    Scanners(const Scanners&) = default;
    Scanners(Scanners&&)      = default;
    /*!
     * @brief nothing to do as of this version.
     */
    ~Scanners()                      = default;
    
    ConfigData& Config() { return mConfig; }
    
    Util::Expect<std::size_t> Scan();
    
private:
    ConfigData mConfig;
    
    void Append(TokenData& Token_) ;
    
    #pragma region Scanners
    
    Scanners::Return Number(TokenData&);
    Scanners::Return Identifier(TokenData&);
    Scanners::Return Literal(TokenData&);
    
    #pragma endregion Scanners
    
};
}


//#endif //UTIL_LEXER_H

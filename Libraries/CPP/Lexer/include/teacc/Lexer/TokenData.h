//
// Created by bretzel on 20-04-20.
//

//#ifndef UTIL_TOKENDATA_H
//#define UTIL_TOKENDATA_H

#pragma once
#include <teacc/Lexer/Types.h>
#include <vector>

namespace teacc
{

struct LEXER_LIB TokenData
{
    Lexem::Mnemonic C   = Lexem::Mnemonic::noop;
    Type::T        T  =  Type::null;    ///< Primitive Type bit.
    Type::T        S   = Type::null;	///< Semantic Type bits field
    Delta::T D = Delta::noop;
    void* mData  = nullptr;
    
    using Collection    = std::vector<TokenData>;
    using Iterator      = Collection::iterator;
    
    
    struct LEXER_LIB  LocationData{
        const char* Begin = nullptr;
        const char* End = nullptr;
        int L         = -1; ///< line number
        int C         = -1; ///< Column number
        int64_t I     = -1; ///< Absolute Offset from the beginning of the Source Text.
        std::string   operator()();
        std::string   Text();
        std::string   Position();
    } mLoc;
    
    struct LEXER_LIB Flag {
        int8_t V : 1; ///< Pre-parsed as a value TokenData;
        int8_t S : 1; ///< Post parsed as assignable
        int8_t M : 1; ///< Virtual multiplication operator. (...4ac...)
    } mFlags = {0,0,0};
    
    static TokenData mNull;
    
    TokenData()=default;
    ~TokenData() = default;
    
    TokenData(Lexem::Mnemonic Code_, Type::T Type_, Type::T Sem_, Delta::T Delta_, Lexem::T aLexem,  int8_t V);
    TokenData(Lexem::Mnemonic Code_, Type::T Type_, Type::T Sem_, Delta::T Delta_, TokenData::LocationData LocationData_, TokenData::Flag Flags_, void* Ptr_=nullptr);
    TokenData(const TokenData& Token_);
    TokenData(TokenData&& Token_)noexcept;
    
    TokenData& operator=(TokenData&& Token_)noexcept;
    TokenData& operator=(const TokenData& Token_);
    TokenData  operator[](Lexem::Mnemonic CC);
    //TokenData* ptr() { return this; }
    std::string Mark();
    
    
    explicit operator bool() const  { return mLoc.Begin != nullptr; }
    bool operator || (Type::T Sem_) const  { return S || Sem_; }
    
    [[nodiscard]] std::string Attr()  { return mLoc(); }
    [[nodiscard]] std::string SemanticTypes();
    [[nodiscard]] std::string TypeName();
    [[nodiscard]] std::string Details();
    
    static TokenData Scan(const char* C_);
    static std::string Str(Type::T Type_);
    static Type::T     Int(const std::string&);
    
    
    [[nodiscard]] bool IsBinary()        const{return S & Type::binary;}
    [[nodiscard]] bool isUnary()         const{return S & Type::unary;}
    [[nodiscard]] bool isIdentifier()    const{return S & Type::id;}
    [[nodiscard]] bool isLeaf()          const{return S & Type::leaf;}
    [[nodiscard]] bool isOperator()      const{return S & Type::oper;}
    [[nodiscard]] bool isClosing_pair()  const{return S & Type::closepar;}
    [[nodiscard]] bool isPunctuation()   const{return S & Type::punctuation;}
    [[nodiscard]] bool isNumber()        const{return S & Type::number;}
    [[nodiscard]] bool isHexadecimal()   const{return S & Type::hex;}
    [[nodiscard]] bool isPrefix()        const{return S & Type::prefix;}
    [[nodiscard]] bool isPostfix()       const{return S & Type::postfix;}
    [[nodiscard]] bool isInstruction()   const{return !(S & (Type::oper | Type::leaf));}
    
    
    
    /*
        // Still to do:

    static TokenData query(Type::t ty);
    static TokenData query(Lexem::t lx);
    static TokenData query(Mnemonic a_code);
    static Mnemonic strtoMnemonic(const std::string &k);

    */
    

};







}

//#endif //UTIL_TOKENDATA_H

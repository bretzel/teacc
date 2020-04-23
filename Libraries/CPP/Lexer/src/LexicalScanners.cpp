//
// Created by bretzel on 20-04-22.
//

#include <teacc/Lexer/LexicalScanners.h>
#include <cstring>

namespace teacc::Lexer
{


#pragma region InternalCursor

/*!
 * @brief Skips white spaces character, advancing(/consuming) C pointer
 *
 * Prefix increment operator
 * @return true if C is not on EOF, false otherwise.
 */
bool LexicalScanners::InternalCursor::operator++()
{
    if(C>=E) return false;
    ++C;
    while((C < E) && (!isalnum(*C))) ++C;
    return true;
}

/*!
 * @brief Skips white spaces character, advancing(/consuming) C pointer
 *
 * Postfix increment operator, just calls the prefix increment operator.
 * @return true if C is not on EOF, false otherwise.
 */
bool LexicalScanners::InternalCursor::operator++(int)
{
    return ++(*this);
}

/*!
 * @brief Skips white spaces character, advancing(/consuming) C pointer
 *
 * Named method, just calls the prefix increment operator.
 * @return true if C is not on EOF, false otherwise.
 */
bool LexicalScanners::InternalCursor::SkipWS()
{
    return ++(*this);
}

/*!
 * @brief Tests if P is on or past EOF.
 * @param P
 * @return true if P is EOF, false otherwise.
 */
bool LexicalScanners::InternalCursor::Eof(const char *P)
{
    if(P)
        return P > E;
    return C > E;
}

/*!
 * @brief Synchronize the Location data from the C pointer.
 *
 * @return none.
 */
void LexicalScanners::InternalCursor::Sync()
{
    L = 1;
    const char* Pos_  = C;
    while(C>B)
    {
        if((*Pos_ == '\n') || (*Pos_ == '\r')) ++L;
        --C;
    }
    
    Pos_ = C;
    Col = 1;
    while((C>B) && (*C != '\n') && (*C != '\r'))
    {
        --C;
        ++Col;
    }
}

/*!
 * @brief Get the ptrdiff between the C pointer and the beginning of the source text (B pointer).
 * @return int.
 */
int LexicalScanners::InternalCursor::Index()
{
    return C-B;
}

/*!
 * @brief Advances/Consume the C pointer till the next NewLine{'\r'; '\n'}  code in the source text
 * @return distinct std::string of the sequence.
 */
std::string LexicalScanners::InternalCursor::ScanToEol()
{
    std::string Str;
    while( (C <= E ) && (*C != '\n') && (*C != '\r')) Str += *C++;
    return Str;
}

/*!
 * @brief Get a std::string copy of the current line from the C pointer
 * @return string.
 */
std::string LexicalScanners::InternalCursor::Line()
{
    std::string Str;
    
    const char* lb, *eb;
    lb = eb = C;
    while((lb>B) && (*lb!='\r') && (*lb != '\n')) --lb;
    if(lb>B) ++lb;
    while((eb<E) && (*eb != '\r') && (*eb != '\n')) ++eb;
    --eb;
    
    for(;lb<=eb; lb++) Str += *lb;
    return Str;
}

/*!
 * @brief Build a line String from the current position then Mark at the current columns.

  * @return std::string
  * @note : Must be Sync()'ed before calling Mark();
 
 */
std::string LexicalScanners::InternalCursor::Mark()
{
    Util::String Str = Line();
    Str << '\n';
    for(int x=0; x<Col; x++) Str << ' ';
    Str << '^';
    return Str();
}

/*!
 * @brief Get the string representation of the [internal]cursor location in the source text.
 * @return std::string
 */
std::string LexicalScanners::InternalCursor::Location()
{
    Util::String Str = "%d,%d";
    Str << L << Col;
    return Str();
}


/*!
 * @brief Advances/Consumes the C pointer to Skip till SubStr_ match.
 * @param SubStr_
 * @return Expect code.
 */
Util::Rem::Int LexicalScanners::InternalCursor::ScanTo(const char *SubStr_)
{
    
    return Util::Rem::Int::Ok;
}


Util::Expect<std::string> LexicalScanners::InternalCursor::ScanString()
{
    const char* be = C;
    char Quote_ = *be;
    std::string Str;
    while((be <= E) && (*be != Quote_))Str += *be++;
    if((*be != Quote_) && (be > E))
    {
        Sync();
        return (
            Util::Rem::Save()
            << Util::Rem::Type::Error << Util::Rem::Int::Eof
            << " : Unterminated string constant:\n"
            << Mark()
        );
    }
    Str += *be; // Include the rhs Quote.
    return Str;
}

LexicalScanners::InternalCursor::InternalCursor(const char *Source_)
{
    C = Source_;
    E = C + std::strlen(C) -1;
    B = C;
    L = Col = 1;
}


#pragma endregion InternalCursor

//---------------------------------------------------------------------------------------------------------------------------
#pragma region NumSCanner
LexicalScanners::NumScanner::NumScanner(const char *_c, const char *_eos): B(_c), E(_eos), Eos(_eos){}

/*!
 * @brief For now a bare minimum digit with some rough floating point scan.
 * @return true if the C pointer is consumed and advanced
 */
bool LexicalScanners::NumScanner::operator++(int)
{
    if(C >= E)
        return false;
    
    if(!isdigit(*C))
    {
        if(*C == '.')
            if(!Real)
                Real = true;
            else
                return false;
        else
            return false;
    }
    ++C;
    return true;
}


/*!
 * @brief Implements boolean operator
 * @return true if this NumScanner was  a valid numeric sequence, false otherwise.
 */
LexicalScanners::NumScanner::operator bool()
{
    return false;
}

/*!
 * @brief Computes the numeric scale and 'best gess' base.
 * @return one [combined] of {{u,i}{8,16,32,64}} | real| oct | hex | bin.
 *
 * @note Numeric Base is omitted as of this version. Thus it only computes the Scale.
 */
Type::T LexicalScanners::NumScanner::operator()()
{
    
    if(!Real)
    {
        Util::String Str;
        Str = Str.MakeStr(C,E);
        uint64_t D;
        Str >> D;
        uint64_t I = 0;
        std::array<uint64_t,3> R = {0x100,0x10000,0x100000000};
        while(D >= R[I]) ++I;
        std::array<Type::T,4> Cap = {
            Type::u8, Type::u16, Type::u32, Type::u64
        };
        return Cap[I];
    }
    
    ///@todo SCAN SCIENTIFIC NOTATION !!!!!!
    return Type::real;
}

#pragma endregion NumSCanner


#pragma region Scanners


using Util::Rem;


Util::Expect<std::size_t> LexicalScanners::Scan()
{
    if((!mConfig.mSource) || (!mConfig.mTokensCollection))
        return (
            Rem::Save() << Rem::Type::Error << " :-> " << Rem::Int::UnExpected << " nullptr on Source Text or Tokens Collection Stream."
        );
    Util::Expect<> Number(TokenData&);
    mCursor = InternalCursor(mConfig.mSource);
    Util::Expect<> R;
    
    while(mCursor.Eof())
    {
        TokenData Token_ = TokenData::Scan(mCursor.C);
        if(!Token_)
        {
            // Try literal numeric expr:
            if((R = Number(Token_)))
            {
                if(*R == Rem::Int::Rejected)
                {
                    if(!(R = Identifier(Token_)))
                        return R();
                }
            }
            return R();
        }
        else // [Pre]Analyse further
        {
            ///@todo Place to the lexical analyzers map!
//            return (
//                Rem::Save() <<
//                Rem::Type::Message <<
//                Rem::Int::Implement << ": " <<
//                " Lexical Analyzers are not yet defined :" <<
//                Token_.Mark()
//            );
            ;
        }
        return (
                Rem::Save() <<
                Rem::Type::Message <<
                Rem::Int::Implement << ": " <<
                " Lexical Analyzers are not yet defined :" <<
                Token_.Mark()
        );
    }
    return static_cast<std::size_t>(Rem::Int::Rejected);
}



Util::Expect<> LexicalScanners::Number(TokenData& Token_)
{
    NumScanner Num_ = {mCursor.C, mCursor.E};
    while(Num_++);
    if(!Num_)
        return Rem::Int::Rejected;
    
    // It is:
    
    // Update data : (Token_ and mCursor)
    mCursor.Sync();
    Type::T S = Num_();
    Token_ = {
        Lexem::Mnemonic::noop,
        S,
        Type::number | S,
        Delta::identifier,
        {Num_.B, Num_.E, mCursor.L, mCursor.Col, mCursor.Index()},
        {1,0,0},
        nullptr
    };
    // ...
    Append(Token_);
    return Rem::Int::Accepted;
}


#pragma endregion Scanners

void LexicalScanners::Append(TokenData &Token_)
{
    // Consume the Cursor the length of the Token [text] Attribute.
    //...
    mConfig.mTokensCollection->push_back(Token_);
}


}

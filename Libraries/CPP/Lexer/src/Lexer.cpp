//
// Created by bretzel on 20-04-22.
//

#include <teacc/Lexer/Lexer.h>
#include <cstring>


using teacc::Util::Rem;

namespace teacc::Lexer
{

#pragma region InternalCursor

/*!
 * @brief Skips white spaces character, advancing(/consuming) C pointer
 *
 * Prefix increment operator
 * @return true if C is not on EOF, false otherwise.
 */
bool Scanners::InternalCursor::operator++()
{
    if(C >= E)
        return false;
    ++C;
    while((C < E) && (!isalnum(*C)))
        ++C;
    return true;
}

/*!
 * @brief Skips white spaces character, advancing(/consuming) C pointer
 *
 * Postfix increment operator, just calls the prefix increment operator.
 * @return true if C is not on EOF, false otherwise.
 */
bool Scanners::InternalCursor::operator++(int)
{
    return ++(*this);
}

 /*!
 * @brief Skips white spaces character, advancing(/consuming) C pointer
 *
 * Named method, just calls the prefix increment operator.
 * @return true if C is not on EOF, false otherwise.
 */
[[maybe_unused]] bool Scanners::InternalCursor::SkipWS()
{
    return ++(*this);
}

/*!
 * @brief Tests if P is on or past EOF.
 * @param P
 * @return true if P is EOF, false otherwise.
 */
bool Scanners::InternalCursor::Eof(const char *P) const
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
void Scanners::InternalCursor::Sync()
{
    L = 1;
    while(C > B)
    {
        if((*C == '\n') || (*C == '\r'))
            ++L;
        --C;
    }
    
    Col = 1;
    while((C > B) && (*C != '\n') && (*C != '\r'))
    {
        --C;
        ++Col;
    }
}


/*!
 * @brief Get the ptrdiff between the C pointer and the beginning of the source text (B pointer).
 * @return int.
 */
long Scanners::InternalCursor::Index() const
{
    return (ptrdiff_t) (C - B);
}

/*!
 * @brief Advances/Consume the C pointer till the next NewLine{'\r'; '\n'}  code in the source text
 * @return distinct std::string of the sequence.
 */
[[maybe_unused]] std::string Scanners::InternalCursor::ScanToEol()
{
    std::string Str;
    while((C <= E) && (*C != '\n') && (*C != '\r'))
        Str += *C++;
    return Str;
}

/*!
 * @brief Get a std::string copy of the current line from the C pointer
 * @return string.
 */
std::string Scanners::InternalCursor::Line() const
{
    std::string Str;
    
    const char *lb, *eb;
    lb = eb = C;
    while((lb > B) && (*lb != '\r') && (*lb != '\n'))
        --lb;
    if(lb > B)
        ++lb;
    while((eb < E) && (*eb != '\r') && (*eb != '\n'))
        ++eb;
    --eb;
    
    for(; lb <= eb; lb++)
        Str += *lb;
    return Str;
}

/*!
 * @brief Build a line String from the current position then Mark at the current columns.

  * @return std::string
  * @note : Must be Sync()'ed before calling Mark();
 
 */
std::string Scanners::InternalCursor::Mark() const
{
    Util::String Str = Line();
    Str << '\n';
    for(int x = 0; x < Col; x++)
        Str << ' ';
    Str << '^';
    return Str();
}

/*!
 * @brief Get the string representation of the [internal]cursor location in the source text.
 * @return std::string
 */
[[maybe_unused]] std::string Scanners::InternalCursor::Location() const
{
    Util::String Str = "%d,%d";
    Str << L << Col;
    return Str();
}

void Scanners::Append(TokenData &Token_) const
{
    // Consume the Cursor the length of the Token [text] Attribute.
    //...
    mConfig.mTokensCollection->push_back(Token_);
}

/*!
 * @brief Advances/Consumes the C pointer to Skip till SubStr_ match.
 * @param SubStr_
 * @return Expect code.
 */
[[maybe_unused]] Rem::Int Scanners::InternalCursor::ScanTo(const char *SubStr_)
{
    
    return Util::Rem::Int::Ok;
}

teacc::Util::Expect<std::string> Scanners::InternalCursor::ScanString()
{
    const char *be = C;
    char Quote_ = *be;
    std::string Str;
    while((be <= E) && (*be != Quote_))
        Str += *be++;
    if((*be != Quote_) && (be > E))
    {
        Sync();
        return (Util::Rem::Save() << Util::Rem::Type::Error << Util::Rem::Int::Eof << " : Unterminated string constant:\n" << Mark());
    }
    Str += *be; // Include the rhs Quote.
    return Str;
}

Scanners::InternalCursor::InternalCursor(const char *Source_)
{
    C = Source_;
    E = C + std::strlen(C) - 1;
    B = C;
    L = Col = 1;
}

#pragma endregion InternalCursor

//---------------------------------------------------------------------------------------------------------------------------
#pragma region NumSCanner
Scanners::NumScanner::NumScanner(const char *_c, const char *_eos) : B(_c), C(_c), E(_eos), Eos(_eos)
{
    std::cout << __PRETTY_FUNCTION__ << ": B:" << *B << "->\n";
}

/*!
 * @brief For now a bare minimum digit with some rough floating point scan.
 * @return true if the C pointer is consumed and advanced
 */
bool Scanners::NumScanner::operator++(int)
{
    std::cout << __PRETTY_FUNCTION__ << "C:'" << *C << "'";
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
Scanners::NumScanner::operator bool()
{
    return false;
}

/*!
 * @brief Computes the numeric scale and 'best gess' base.
 * @return one [combined] of {{u,i}{8,16,32,64}} | real| oct | hex | bin.
 *
 * @note Numeric Base is omitted as of this version. Thus it only computes the Scale.
 */
Type::T Scanners::NumScanner::operator()()
{
    
    if(!Real)
    {
        Util::String Str;
        Str = Str.MakeStr(C, E);
        uint64_t D;
        Str >> D;
        uint64_t I = 0;
        std::array<uint64_t, 3> R = {0x100, 0x10000, 0x100000000};
        while(D >= R[I])
            ++I;
        std::array<Type::T, 4> Cap = {Type::u8, Type::u16, Type::u32, Type::u64};
        return Cap[I];
    }
    
    ///@todo SCAN SCIENTIFIC NOTATION !!!!!!
    return Type::real;
}

#pragma endregion NumSCanner

#pragma region Scanners

teacc::Util::Expect<std::size_t> Scanners::Scan()
{
   
    if((!mConfig.mSource) || (!mConfig.mTokensCollection))
        return (Rem::Save() << Rem::Type::Error << " :-> " << Rem::Int::UnExpected << " nullptr on Source Text or Tokens Collection Stream.");
    
    mCursor = InternalCursor(mConfig.mSource);
    std::cout << __PRETTY_FUNCTION__ << "Cursor: '" << mCursor.B << "'\n";
    Return R;
    
    while(!mCursor.Eof())
    {
        TokenData Token_ = TokenData::Scan(mCursor.C);
        if(!Token_)
        {
            std::cout << "Lexer: Not a Ref Token:\n";
            // Try literal numeric expr:
            if(!(R = Number(Token_)))
            {
                std::cout << "Lexer: Not a number:\n";
                if(*R == Rem::Int::Rejected)
                {
                    if(!(R = Identifier(Token_)))
                        return R();
                }
            }
        }
        else // [Pre]Analyse further
        {
            std::cout << Token_.Details() << '\n';
            ///@todo Place to the lexical analyzers map!
                        return (
                            Rem::Save() <<
                            Rem::Type::Message <<
                            Rem::Int::Implement << ": " <<
                            " Lexical Analyzers are not yet defined :" <<
                            Token_.Mark()
                        );
            ;
        }
        return (Rem::Save() << Rem::Type::Message << Rem::Int::Implement << ": " << " Lexical Analyzers are not yet defined :" << Token_.Mark());
    }
    return static_cast<std::size_t>(Rem::Int::Rejected);
}



Scanners::Return Scanners::Number(TokenData &Token_)
{
    
    std::cout << __PRETTY_FUNCTION__ << ":\n";
    NumScanner Num_ = {mCursor.C, mCursor.E};
    std::cout << " OK pas planté encore...{" << Num_.C << "}\n";
    while(Num_++);
    if(!Num_)
        return Rem::Int::Rejected;
    
    // It is:
    
    // Update data : (Token_ and mCursor)
    mCursor.Sync();
    Type::T S = Num_();
    Token_ = {Lexem::Mnemonic::noop, S, Type::number | S, Delta::identifier, {Num_.B, Num_.E, mCursor.L, mCursor.Col, mCursor.Index()}, {1, 0, 0}, nullptr};
    
    if( !(Token_.S & Type::real))
    {
        Util::String str;
        str << Token_.Attr();
        uint64_t D=0;
        std::istringstream i(str.c_str());
        switch(Num_.Num)
        {
            case NumScanner::Bin:
                //????????? ah!
                break;
            case NumScanner::Oct:
                i >> std::oct >> D;
                break;
            case NumScanner::Dec:
                i >> D;
                break;
            case NumScanner::Hex:
                i >> std::hex >> D;
                break;
            default:
                str >> D;
                break;
        }
        
        //std::cout << __PRETTY_FUNCTION__ << " Parsed number:" << D << '\n';
        uint64_t n = 0;
        std::array<uint64_t,3> R = {0x100,0x10000,0x100000000};
        while(D >= R[n])
            ++n;
        
        switch(n)
        {
            case 0:Token_.S = (Token_.S & ~Type::u64) | Type::u8;
                break;
            case 1:Token_.S = (Token_.S & ~Type::u64) | Type::u16;
                break;
            case 2:Token_.S = (Token_.S & ~Type::u64) | Type::u32;
                break;
            default:Token_.S= (Token_.S & ~Type::u64) | Type::u64;
                break;
        }
    }
    // ...
    Append(Token_);
    return Rem::Int::Accepted;
}


Scanners::Return Scanners::Identifier(TokenData &Token_)
{
    const char* C = mCursor.C;
    if( !(std::isalpha(*C)) && (*C != '_') )
        return Rem::Int::Rejected;
    
    ++C;
    while (std::isalnum(*C) || (*C=='_')) ++C;
    
    if (C <= mCursor.C)
        return Rem::Int::Rejected;
    
    --C;
    Token_.mLoc.Begin = mCursor.C;
    Token_.mLoc.End = C;
    Token_.mLoc.C = mCursor.Col;
    Token_.mLoc.L = mCursor.L;
    Token_.mLoc.I = mCursor.Index(); ///@todo Reduce overhead.
    Token_.C = Lexem::Mnemonic::noop;
    Token_.T = Type::id;
    Token_.mFlags = { 1,0,0 };
    Token_.S = Type::leaf | Type::id;
    Token_.D = Delta::identifier;
    //LogDebugFn << " Attribute: [" << Token_.attribute() << ']' << Ends;
    return Rem::Int::Accepted;
}



Scanners::Return Scanners::Literal(TokenData &Token_)
{
    
    const char* i = mCursor.C; // i on the quote lexem
    const char q = *i;
    const char* c;
    std::string litteral;
    //LogDebugFn << " Cursor on " << i << Ends;
    ///*if (i == nullptr)
    //    return {};*/
    //if (result r; !(r = scan_unexpected(Token_))) return r; // Sous reserve
    ++i; c = i;
    Token_.mLoc.Begin = mCursor.C;
    while (!mCursor.Eof(i) && (*i && (*i != q))) {
//        //std::cerr << "i on '" << *i << "'\n";
//        // Note '\n' est UN BYTE. == (int)10.
//        if (*i == '\\') { // Sauf si on a explicitement '\\' dans la string.
//            ++i;
//            if (mCursor.Eof(i)) {
//                std::cout << " eof in \"" << litteral << "\"....\n";
//                return {};
//            }
//            switch (*i) { // On garde le switch-case. Faire une (std::)map serait, je crois, plus coûteux en resources ici.
//                case 'n':
//                    litteral += (char)10; ++i; // Codé à la dur mais c<est pourtant universellement le code ascii assigné
//                    break;
//                case 'r':
//                    litteral += (char)13; ++i;
//                    break;
//                case 't':
//                    litteral += (char)8; ++i;
//                    break;
//                case 'a': // on le garde. Oops. je m'en souviens plus, du code ASCII.... :)
//                    ++i;
//                    break;
//                case 'c':
//                    litteral += (char)3; ++i;
//                    break;
//                case '0': // Okay oui. ( code ASCII de EOF )
//                    litteral += (char)0; ++i;
//                    break;
//                case 'e':
//                    litteral += (char)27; ++i;
//                    break;
//                    ///@Todo  Continuer d'analyser les characteres de contr&ocirc;le.
//                default:
//                    litteral += *i++;
//                    break;
//            }// end switch
//            continue;
//        } // end if '\\';
        litteral += *i++;
    }
    if (mCursor.Eof(i)) {
        std::cout << " eof ->  scanned: \"" << litteral << "\"....\n";
        goto UnterminatedError;
    }
    //--i;
    //std::cerr << "end : i on '" << *i << "'\n";
    //if (/* *i && (*/*i == q/*)*/) {
    mCursor.Sync();
    Token_.mLoc.Begin = mCursor.C; // +1;
    Token_.mLoc.End = i;
    Token_.mLoc.L = mCursor.L;
    Token_.mLoc.C = mCursor.Col;
    
    Token_.C = Lexem::Mnemonic::noop;
    Token_.T = Type::text;
    Token_.S = Type::text | Type::leaf;
    std::cerr << "Litteral accepted:token_t[" << Token_.Attr() << "]\n";
    return { Rem::Int::Accepted };
    //}
    UnterminatedError:
    Token_.mLoc.Begin = mCursor.C;
    Token_.mLoc.End = mCursor.C; ///@todo  D&eacute;terminer la s&eacute;quence &agrave; fournir.
    Token_.mLoc.I = mCursor.C - mCursor.B;
    Token_.mLoc.L = mCursor.L;
    Token_.mLoc.C = mCursor.Col;
    
    return (
        Rem::Save() << Rem::Type::Error << ": " <<  Rem::Int::Unterminated << '\n' << Token_.Mark()
    );
}

#pragma endregion Scanners

}


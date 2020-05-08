//
// Created by bretzel on 20-04-20.
//

#include <teacc/Lexer/TokenData.h>
#include <teacc/Util/String.h>

#include <map>


namespace teacc{

TokenData TokenData::mNull = TokenData();

namespace Type
{
std::map<T, std::string> T_STR = {{null,        "null"},
                                  {number,      "number"},
                                  {text,        "text"},
                                  {voidptr,     "voidptr"},
                                  {any,         "any"},
                                  {leaf,    "leaf"},
                                  {sign,    "sign"},
                                  {i8,      "i8"},
                                  {i16,     "i16"},
                                  {i32,     "i32"},
                                  {i64,     "i64"},
                                  {u8,      "u8"},
                                  {u16,     "u16"},
                                  {u32,     "u32"},
                                  {u64,     "u64"},
                                  {fp,      "fp"},
                                  {var,     "var"},
                                  {bloc,    "bloc"},
                                  {filo,    "filo"},
                                  {keyword, "keyword"},
                                  {unary,   "unary"},
                                  {prefix,  "prefix"},
                                  {postfix, "postfix"},
                                  {oper,    "operator"},
                                  {binary,  "binary"},
                                  {func,    "rtfn"},
                                  {funcptr,     "rtfn ptr"},
                                  {obj,         "object"},
                                  {pointer,     "pointer"},
                                  {type,        "t"},
                                  {id,          "identifier"},
                                  {ref,         "reference"},
                                  {punctuation, "punctuation"},
                                  {assign,      "assign"},
                                  {boolean,     "boolean"},
                                  {hex,         "hex"},
                                  {bin,         "bin"},
                                  {octal,       "oct"},
                                  {f32,         "f32"},
                                  {f64,         "f64"},
                                  {f128,        "f128"},
                                  {leftpar,     "leftpar"},
                                  {closepar,    "closepar"},
                                  {openabs,     "openabs"},
                                  {closeabs,    "closeabs"},
                                  {static_t,    "static"}};

std::map<std::string, T> STR_T = {{"null",         null},
                                  {"number",       number},
                                  {"text",         text},
                                  {"string",       text},
                                  {"voidptr",      voidptr},
                                  {"void-pointer", voidptr},
                                  {"any",          any},
                                  {"leaf",     leaf},
                                  {"sign",     sign},
                                  {"i8",       i8},
                                  {"i16",      i16},
                                  {"i32",      i32},
                                  {"i64",      i64},
                                  {"u8",       u8},
                                  {"u16",      u16},
                                  {"u32",      u32},
                                  {"u64",      u64},
                                  {"fp",     fp},
                                  {"var",      var},
                                  {"variable", var},
                                  {"bloc",     bloc},
                                  {"filo",     filo},
                                  {"stack",    filo},
                                  {"keyword",  keyword},
                                  {"unary",    unary},
                                  {"prefix",   prefix},
                                  {"postfix",  postfix},
                                  {"oper",     oper},
                                  {"operator",     oper},
                                  {"binary",       binary},
                                  {"binary-op",    binary},
                                  {"func",         func},
                                  {"rtfn",         func},
                                  {"funcptr",      funcptr},
                                  {"rtfn-pointer", funcptr},
                                  {"obj",          obj},
                                  {"object",       obj},
                                  {"pointer",      pointer},
                                  {"t",            type},
                                  {"id",           id},
                                  {"identifier",   id},
                                  {"ref",          ref},
                                  {"reference",    ref},
                                  {"punctuation",  punctuation},
                                  {"assign",       assign},
                                  {"boolean",      boolean},
                                  {"hex",          hex},
                                  {"leftpar",      leftpar},
                                  {"closepar",     closepar},
                                  {"openabs",      openabs},
                                  {"closeabs",     closeabs}};
}

std::string TokenData::Str(Type::T Type_)
{
    Type::T tbm = Type_;
    Util::String Text_;
    int a, c, b;
    
    for(const auto &t : Type::T_STR)
    {
        if(!tbm)
            break;
        if(t.first & tbm)
        {
            Text_ << t.second;
            tbm &= ~t.first;
            if(tbm)
                Text_ << '/';
        }
    }
    if(Text_.Empty())
        Text_ = "null";
    return Text_();
}




TokenData::TokenData(Lexem::Mnemonic Code_, Type::T Type_, Type::T Sem_, Delta::T Delta_, Lexem::T aLexem, int8_t V)
{
    M = Code_;
    T = Type_;
    S = Sem_;
    D = Delta_;
    mLoc = {aLexem, nullptr, 0, 0, -1};
    mFlags = {0, 0, 0};
}

TokenData::TokenData(Lexem::Mnemonic Code_, Type::T Type_, Type::T Sem_, Delta::T Delta_, TokenData::LocationData LocationData_, TokenData::Flag Flags_, void *Ptr_)
{
    M       = Code_;
    T       = Type_;
    S       = Sem_;
    D       = Delta_;
    mLoc    = LocationData_;
    mFlags  = Flags_;
    mData   = Ptr_;
}

TokenData::TokenData(const TokenData &Token_)
{
    M       = Token_.M;
    T       = Token_.T;
    S       = Token_.S;
    D       = Token_.D;
    mLoc    = Token_.mLoc;
    mFlags  = Token_.mFlags;
    mData   = Token_.mData;
}

TokenData::TokenData(TokenData &&Token_) noexcept
{
    std::swap(M       , Token_.M);
    std::swap(T       , Token_.T);
    std::swap(S       , Token_.S);
    std::swap(D       , Token_.D);
    std::swap(mLoc    , Token_.mLoc);
    std::swap(mFlags  , Token_.mFlags);
    std::swap(mData   , Token_.mData);
}

TokenData &TokenData::operator=(TokenData &&Token_) noexcept
{
    std::swap(M       , Token_.M);
    std::swap(T       , Token_.T);
    std::swap(S       , Token_.S);
    std::swap(D       , Token_.D);
    std::swap(mLoc    , Token_.mLoc);
    std::swap(mFlags  , Token_.mFlags);
    std::swap(mData   , Token_.mData);
    return *this;
}

TokenData &TokenData::operator=(const TokenData &Token_)
{
    M       = Token_.M;
    T       = Token_.T;
    S       = Token_.S;
    D       = Token_.D;
    mLoc    = Token_.mLoc;
    mFlags  = Token_.mFlags;
    mData   = Token_.mData;
    return *this;
}




Type::T Int(const std::string &a_names)
{
    Util::String::Word::Collection Array;
    Util::String  names = a_names;
    
    Type::T result = 0;
    std::size_t count = names.Words(Array, Util::String::DefaultSeparators(), false);
    if(count > 0)
    {
        for(auto s : Array)
        {
            std::string txt = s();
            result |= Type::STR_T[txt];
        }
    }
    return result;
}



static TokenData::Collection TokensRefTable = {
    {Lexem::Mnemonic::knull,        Type::keyword,     0x000040000,  Delta::identifier, Lexem::knull,        1},
    {Lexem::Mnemonic::lshift,       Type::binary,      0x000C00000,  Delta::shift,      Lexem::lshift,       1},
    {Lexem::Mnemonic::openabs,      Type::openabs,     0x080C00000,  Delta::par,        Lexem::openabs,      1},
    {Lexem::Mnemonic::closeabs,     Type::closeabs,    0x080C00000,  Delta::par,        Lexem::closeabs,     1},
    {Lexem::Mnemonic::radical,      Type::binary,      0x000C00000,  Delta::exponent,   Lexem::radical,      1},
    {Lexem::Mnemonic::exponent,     Type::binary,      0x000C00000,  Delta::exponent,   Lexem::exponent,     1},
    {Lexem::Mnemonic::rshift,       Type::binary,      0x000400000,  Delta::shift,      Lexem::rshift,       1},
    {Lexem::Mnemonic::bitxor,       Type::binary,      0x000C00000,  Delta::bits,       Lexem::bitxor,       1},
    {Lexem::Mnemonic::decr,         Type::unary,       0x000580000,  Delta::unary,      Lexem::decr,         1},
    {Lexem::Mnemonic::incr,         Type::unary,       0x000580000,  Delta::unary,      Lexem::incr,         1},
    {Lexem::Mnemonic::assignadd,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignadd,    1},
    {Lexem::Mnemonic::assignsub,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignsub,    1},
    {Lexem::Mnemonic::assignmul,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignmul,    1},
    {Lexem::Mnemonic::assigndiv,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assigndiv,    1},
    {Lexem::Mnemonic::assignmod,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignmod,    1},
    {Lexem::Mnemonic::assignand,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignand,    1},
    {Lexem::Mnemonic::assignor,     Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignor,     1},
    {Lexem::Mnemonic::assignxor,    Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignxor,    1},
    {Lexem::Mnemonic::assignx1,     Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignx1,     1},
    {Lexem::Mnemonic::assignlshift, Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignlshift, 1},
    {Lexem::Mnemonic::assignrshift, Type::assign,      0x100C40000,  Delta::assign,     Lexem::assignrshift, 1},
    {Lexem::Mnemonic::leq,          Type::binary,      0x200C00000,  Delta::less,       Lexem::lteq,         1},
    {Lexem::Mnemonic::geq,          Type::binary,      0x200C00000,  Delta::less,       Lexem::gteq,         1},
    {Lexem::Mnemonic::eq,           Type::binary,      0x200C00000,  Delta::less,       Lexem::eq,           1},
    {Lexem::Mnemonic::neq,          Type::binary,      0x200C00000,  Delta::less,       Lexem::neq,          1},
    {Lexem::Mnemonic::add,          Type::binary,      0x000C00000,  Delta::add,        Lexem::add,          1},
    {Lexem::Mnemonic::sub,          Type::binary,      0x000C00000,  Delta::add,        Lexem::sub,          1},
    {Lexem::Mnemonic::mul,          Type::binary,      0x000C00000,  Delta::product,    Lexem::mul,          1},
    {Lexem::Mnemonic::cppcomment,   Type::punctuation, 0x00000,      Delta::noop,       Lexem::cppcomment,   0},
    {Lexem::Mnemonic::modulo,       Type::binary,      0x000C00000,  Delta::product,    Lexem::modulo,       1},
    {Lexem::Mnemonic::lt,           Type::binary,      0x200C00000,  Delta::less,       Lexem::lt,           1},
    {Lexem::Mnemonic::gt,           Type::binary,      0x200C00000,  Delta::less,       Lexem::gt,           1},
    {Lexem::Mnemonic::assign,       Type::assign,      0x100C40000,  Delta::assign,     Lexem::assign,       1},
    {Lexem::Mnemonic::binand,       Type::binary,      0x000C00000,  Delta::bits,       Lexem::binand,       1},
    {Lexem::Mnemonic::binor,        Type::binary,      0x000C00000,  Delta::bits,       Lexem::binor,        1},
    {Lexem::Mnemonic::x2,           Type::prefix,      0x000580000,  Delta::prefix,     Lexem::x2,           1},
    {Lexem::Mnemonic::x1,           Type::prefix,      0x000580000,  Delta::prefix,     Lexem::x1,           1},
    {Lexem::Mnemonic::bitnot,       Type::unary,       0x000580000,  Delta::prefix,     Lexem::bitnot,       1},
    {Lexem::Mnemonic::booland,      Type::binary,      0x200C00000,  Delta::logand,     Lexem::booland,      1},
    {Lexem::Mnemonic::boolor,       Type::binary,      0x200C00000,  Delta::logor,      Lexem::boolor,       1},
    {Lexem::Mnemonic::openpar,      Type::leftpar,     0x880C00000,  Delta::par,        Lexem::openpar,      1},
    {Lexem::Mnemonic::closepar,     Type::closepar,    0x1080C00000, Delta::par,        Lexem::closepar,     1},
    {Lexem::Mnemonic::openindex,    Type::binary,      0x2080C00000, Delta::par,        Lexem::openindex,    1},
    {Lexem::Mnemonic::closeindex,   Type::binary,      0x4080C00000, Delta::par,        Lexem::closeindex,   1},
    {Lexem::Mnemonic::openbrace,    Type::binary,      0x880C00000,  Delta::par,        Lexem::openbrace,    1},
    {Lexem::Mnemonic::closebrace,   Type::binary,      0x1080C00000, Delta::par,        Lexem::closebrace,   1},
    {Lexem::Mnemonic::bcomment,     Type::punctuation, 0x00000,      Delta::noop,       Lexem::bcomment,     0},
    {Lexem::Mnemonic::ecomment,     Type::punctuation, 0x00000,      Delta::noop,       Lexem::ecomment,     0},
    {Lexem::Mnemonic::division,     Type::binary,      0x000C00000,  Delta::product,    Lexem::division,     1},
    {Lexem::Mnemonic::comma,        Type::binary,      0x080C00000,  Delta::comma,      Lexem::comma,        1},
    {Lexem::Mnemonic::scope,        Type::binary,      0x080C00000,  Delta::scope,      Lexem::scope,        1},
    {Lexem::Mnemonic::semicolon,    Type::punctuation, 0x080000000,  Delta::noop,       Lexem::semicolon,    0},
    {Lexem::Mnemonic::colon,        Type::binary,      0x080C00000,  Delta::noop,       Lexem::colon,        0},
    {Lexem::Mnemonic::range,        Type::binary,      0x080C00000,  Delta::scope,      Lexem::range,        1},
    {Lexem::Mnemonic::factorial,    Type::postfix,     0x000580000,  Delta::unary,      Lexem::factorial,    1},
    {Lexem::Mnemonic::positive,     Type::prefix,      0x000580020,  Delta::unary,      Lexem::positive,     1},
    {Lexem::Mnemonic::negative,     Type::prefix,      0x000580020,  Delta::unary,      Lexem::negative,     1},
    {Lexem::Mnemonic::squote,       Type::text,        0x000000012,  Delta::identifier, Lexem::squote,       1},
    {Lexem::Mnemonic::dquote,       Type::text,        0x000000012,  Delta::identifier, Lexem::dquote,       1},
    {Lexem::Mnemonic::kternary,     Type::keyword,     0x000C40000,  Delta::unary,      Lexem::kternary,     1},
    {Lexem::Mnemonic::hash,         Type::prefix,      0x000580000,  Delta::unary,      Lexem::hash,         1},
    {Lexem::Mnemonic::dollard,      Type::prefix,      0x000580000,  Delta::unary,      Lexem::dollard,      1},
    {Lexem::Mnemonic::dot,          Type::binary,      0x080C00000,  Delta::scope,      Lexem::dot,          1},
    {Lexem::Mnemonic::kreturn,      Type::keyword,     0x000040000,  Delta::identifier, Lexem::kreturn,      0},
    {Lexem::Mnemonic::kif,          Type::keyword,     0x000040000,  Delta::identifier, Lexem::kif,          0},
    {Lexem::Mnemonic::kpi,          Type::keyword,     0x000044011,  Delta::identifier, Lexem::kpi,          1},
    {Lexem::Mnemonic::knumber,      Type::prefix,      0x000540001,  Delta::identifier, Lexem::knumber,      1},
    {Lexem::Mnemonic::ku8,          Type::prefix,      0x000540400,  Delta::identifier, Lexem::ku8,          1},
    {Lexem::Mnemonic::ku16,         Type::prefix,      0x000540800,  Delta::identifier, Lexem::ku16,         1},
    {Lexem::Mnemonic::ku32,         Type::prefix,      0x000541000,  Delta::identifier, Lexem::ku32,         1},
    {Lexem::Mnemonic::ku64,         Type::prefix,      0x000542000,  Delta::identifier, Lexem::ku64,         1},
    {Lexem::Mnemonic::ki8,          Type::prefix,      0x000540040,  Delta::identifier, Lexem::ki8,          1},
    {Lexem::Mnemonic::ki16,         Type::prefix,      0x000540080,  Delta::identifier, Lexem::ki16,         1},
    {Lexem::Mnemonic::ki32,         Type::prefix,      0x000540100,  Delta::identifier, Lexem::ki32,         1},
    {Lexem::Mnemonic::ki64,         Type::prefix,      0x000540200,  Delta::identifier, Lexem::ki64,         1},
    {Lexem::Mnemonic::kreal,        Type::prefix,      0x000544000,  Delta::identifier, Lexem::kreal,        1},
    {Lexem::Mnemonic::kstring,      Type::prefix,      0x000540002,  Delta::identifier, Lexem::kstring,      1},
    {Lexem::Mnemonic::kthen,        Type::keyword,     0x000040000,  Delta::identifier, Lexem::kthen,        0},
    {Lexem::Mnemonic::kelse,        Type::keyword,     0x000040000,  Delta::identifier, Lexem::kelse,        0},
    {Lexem::Mnemonic::kconst,       Type::keyword,     0x000040000,  Delta::identifier, Lexem::kconst,       0},
    {Lexem::Mnemonic::kinclude,     Type::keyword,     0x000040000,  Delta::identifier, Lexem::kinclude,     0},
    {Lexem::Mnemonic::kmodule,      Type::keyword,     0x000040000,  Delta::identifier, Lexem::kmodule,      0},
    {Lexem::Mnemonic::kat,          Type::prefix,      0x000580000,  Delta::unary,      Lexem::kat,          1},
    {Lexem::Mnemonic::kprime,       Type::prefix,      0x000580000,  Delta::unary,      Lexem::kprime,       1},
    {Lexem::Mnemonic::kdo,          Type::keyword,     0x000040000,  Delta::noop,       Lexem::kdo,          0},
    {Lexem::Mnemonic::kwhile,       Type::keyword,     0x000040000,  Delta::noop,       Lexem::kwhile,       0},
    {Lexem::Mnemonic::kfor,         Type::keyword,     0x000040000,  Delta::noop,       Lexem::kfor,         0},
    {Lexem::Mnemonic::kuntil,       Type::keyword,     0x000040000,  Delta::noop,       Lexem::kuntil,       0},
    {Lexem::Mnemonic::krepeat,      Type::keyword,     0x000040000,  Delta::noop,       Lexem::krepeat,      0},
    {Lexem::Mnemonic::kswitch,      Type::keyword,     0x000040000,  Delta::noop,       Lexem::kswitch,      0},
    {Lexem::Mnemonic::kcase,        Type::keyword,     0x000040000,  Delta::noop,       Lexem::kcase,        0},
    {Lexem::Mnemonic::ktype,        Type::keyword,     0x000040000,  Delta::noop,       Lexem::ktype,        0},
    {Lexem::Mnemonic::khex,         Type::hex,         0x000040011,  Delta::noop,       Lexem::khex,         1},
    {Lexem::Mnemonic::kHex,         Type::hex,         0x000040011,  Delta::noop,       Lexem::kHex,         1},
    {Lexem::Mnemonic::kcos,         Type::prefix,      0x000580000,  Delta::unary,      Lexem::kcos,         1},
    {Lexem::Mnemonic::kacos,        Type::prefix,      0x0005C0000,  Delta::unary,      Lexem::kacos,        1},
    {Lexem::Mnemonic::ktan,         Type::prefix,      0x0005C0000,  Delta::unary,      Lexem::ktan,         1},
    {Lexem::Mnemonic::katan,        Type::prefix,      0x0005C0000,  Delta::unary,      Lexem::katan,        1},
    {Lexem::Mnemonic::ksin,         Type::prefix,      0x0005C0000,  Delta::unary,      Lexem::ksin,         1},
    {Lexem::Mnemonic::kasin,        Type::prefix,      0x0005C0000,  Delta::unary,      Lexem::kasin,        1},
    {Lexem::Mnemonic::kobject,      Type::keyword,     0x000040000,  Delta::identifier, Lexem::kobject,      0},
    {Lexem::Mnemonic::kstatic,      Type::keyword,     0x000040000,  Delta::identifier, Lexem::kstatic,      0},
    {Lexem::Mnemonic::kme,          Type::keyword,     0x000040000,  Delta::identifier, Lexem::kme,          1}
};



TokenData TokenData::operator[](Lexem::Mnemonic CC)
{
    for(TokenData Tok : TokensRefTable) {
        if(CC == Tok.M)
            return Tok;
    }
    return TokenData();
}
std::string TokenData::Mark()
{
    Util::String str;
    const char *B = mLoc.Begin - mLoc.I;
    //std::string str;
    int l = 1;
    const char *cc = mLoc.Begin;
    // localiser le debut de la ligne;
    while(*cc && (cc > B) && (*cc != '\n') && (*cc != '\r'))
        --cc;
    // debut de la ligne ou de la source:
    if(cc >= B) {
        if((*cc == '\n') || (*cc == '\r'))
            ++cc;
        while(*cc && (*cc != '\n') && (*cc != '\r'))
            str += *cc++;
    }
    Util::String tstr;
    
    tstr << str << '\n';
    for(int x = 1; x < mLoc.C; x++)
        tstr << ' ';
    tstr << '^';
    return tstr();
}



std::string TokenData::SemanticTypes()
{
    return TokenData::Str(S);
}

std::string TokenData::TypeName()
{
    return TokenData::Str(T);
}

TokenData TokenData::Scan(const char *C_)
{
    int unicode = 0;
    int index = 0;
    
    for(auto Tok : TokensRefTable) {
        const char *crs = C_;
        const char *rtxt = Tok.mLoc.Begin;
        std::size_t sz = std::strlen(rtxt);
        if(*crs != *Tok.mLoc.Begin) {
            ++index;
            continue;
        }
        ++index;
        /*
         * I arbitrary assume that the UNICODE UNIT is a signed 16 bits AND THAT THE VALUE OF FIRST BYTE IS NEGATIVE.
         * Then I take the next byte to determine the unicode ...code...
         */
        while((*crs && *rtxt) && (*crs == *rtxt))
        {
            ////std::cout << *crs <<  *rtxt << ">>>";
            if(*crs < 0)
                ++unicode;
            ++crs;
            ++rtxt;
            ////std::cout << *crs << *rtxt << ','; sin0x4A
        }
        
        if(*rtxt == 0)
        {
            if((*crs && (isalnum(*(crs)))) &&(Tok.S & Type::keyword) && !(Tok.S & Type::oper) && (Tok.T != Type::hex)) continue;
            Tok.mLoc.Begin = C_;
            Tok.mLoc.End = Tok.mLoc.Begin + (crs-C_);
            return Tok;
        }
    }
    return TokenData();
}

Type::T TokenData::Int(const std::string &Str_)
{
    Util::String::Word::Collection Words;
    Util::String Text = Str_;
    std::size_t count = Text.Words(Words, "/",false);
    Type::T Type_;
    if(!count)
        return Type::STR_T[Str_];
    
    for(auto W: Words)
        Type_ |= Type::STR_T[W()];
    
    return Type_;
}


std::string TokenData::Details(bool Mark_)
{
    Util::String Str = "Details: '%s': Pos(%d,%d), %s::{%s}";
    Str << Attr() << mLoc.L << mLoc.C << TypeName() << SemanticTypes();
    if(Mark_)
        Str << '\n' << Mark();
    return Str();
}



std::string TokenData::LocationData::operator()()
{
    if(!End || !Begin)
        return std::string();
    return Text();
}

std::string TokenData::LocationData::Text()
{
    if(Begin == nullptr)
        return std::string();
    
    std::string str;
    const char *ptr = Begin;
    
    str += *ptr++;
    if(!End) {
        while(*ptr)
            str += *ptr++;
        return str;
    }
    while(ptr <= End)
        str += *ptr++;
    return str;
}


std::string TokenData::LocationData::Position()
{
    Util::String Txt = "%d,%d";
    Txt << L << C;
    return Txt();
}

}

//
// Created by bretzel on 20-04-17.
//

#include <teacc/Util/String.h>


namespace teacc::Util
{

using std::string;

string UTIL_LIB String::_DefaultSeparators = "\\%(){}[]`$#@!;,~?^&<>=+-*/:.";

string UTIL_LIB String::__nullstr__ = "";

std::ostream &operator<<(std::ostream &in, const String &_s)
{
    in << _s();
    return in;
}

String::String()
{
    // _D has been instanciated here as well...
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.cend();
}

String::String(const char *a_str)
{
    //SOut << __PRETTY_FUNCTION__ << ":[\"" << a_str << "\"]:\n";
    _D = a_str;
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.cend();
}

String::String(std::string &&a_str)
{
    std::swap(_D, a_str);
    a_str.clear();
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.cend();
    
}

String::String(const string &a_str)
{
    //ffnl << a_str << "\n";
    _D = a_str;
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.cend();
    
}

String::String(const String &Str)
{
    //ffnl << Str._str << "\n";
    _D = Str._D;
    _Cursor = Str._Cursor;
}

String::String(String &&Str) noexcept
{
    //ffnl << Str._str << "\n";
    std::swap(_D, Str._D);
    _Cursor = std::move(Str._Cursor);
}

String::~String()
{
    //ffnl << _str << "\n";
    _D.clear();
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.cend();
    
}



//String& String::operator=(const String& a_str)
//{
//    //ffnl << a_str._str << "\n";
//    _D = a_str._D;
//    _ArgPosition = a_str._ArgPosition;
//    _Precision = a_str._Precision;
//    return *this;
//}

String &String::operator=(String &&a_str) noexcept
{
    //ffnl << a_str._str << "\n";
    std::swap(_D, a_str._D);
    _ArgPosition = 0;
    _Cursor = std::move(a_str._Cursor);
    return *this;
}

bool String::operator==(const String &a_str) const
{
    
    return _D == a_str._D;
    
}

String &String::operator=(string &&a_str)
{
    //ffnl << a_str << "\n";
    swap(_D, a_str);
    _ArgPosition = 0;
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = --_D.end();
    
    return *this;
}

String &String::operator<<(char c)
{
    
    if(ScanArg() == std::string::npos)
    {
        _D += c;
        return *this;
    }
    return Printf<char>(c);
    
}

String &String::operator=(const char *a_str)
{
    if(a_str)
        _D = a_str;
    else
        _D = "";
    _ArgPosition = 0;
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.end();
    
    return *this;
}

String &String::operator<<(const string &a_str)
{
    //_scan_next_Arg();
    if(ScanArg() == std::string::npos)
    {
        _D += a_str;
        return *this;
    }
    return Printf<const std::string &>(a_str);
}

String::Collection String::ArgsArray(int argc, char **argv)
{
    Collection args;
    for(int x = 0; x < argc; x++)
    {
        args.push_back(argv[x]);
        
    }
    return args;
}

String &String::operator<<(const String &a_str)
{
    //_scan_next_Arg();
    if(ScanArg() == std::string::npos)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << a_str();
        _D += os.str();
        return *this;
    }
    return Printf<const std::string &>(a_str());
}

String &String::operator<<(const char *a_str)
{
    //_scan_next_Arg();
    if(ScanArg() == std::string::npos)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << a_str;
        _D += os.str();
        return *this;
    }
    return Printf<const char *>(a_str);
}

String &String::operator+=(const String &a_atr)
{
    _D += a_atr._D;
    return *this;
}
String &String::operator+=(const string &a_atr)
{
    _D += a_atr;
    return *this;
    
}

String &String::operator+=(char c)
{
    _D += c;
    return *this;
}

String &String::operator+(char c)
{
    _D += c;
    return *this;
}

String &String::operator+(const String &a_atr)
{
    _D += a_atr._D;
    return *this;
}
String &String::operator+(const string &a_atr)
{
    _D += a_atr;
    return *this;
}

String &String::operator>>(string &_Arg)
{
    _Arg = _D;
    return *this;
}

std::string String::MakeStr(const char *B, const char *E)
{
    std::string Str;
    const char *C = B;
    if((!B) || (!E) || (!*B) || (!*E))
        return Str;
    while(C <= E)
        Str += *C++;
    
    return Str;
}

void String::Clear()
{
    _D.clear();
    _ArgPosition = (string::size_type) 0;
    _Cursor.B = _Cursor.C = _D.cbegin();
    _Cursor.E = _D.end();
    
}

std::string String::DateTime(const std::string &str_fmt)
{
    time_t rawtime;
    struct tm *timeinfo;
    char tmb[180];
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(tmb, 60, str_fmt.c_str(), timeinfo);
    std::string _s = tmb;
    return tmb;
}

string::size_type String::ScanArg()
{
    _ArgPosition = _D.find('%', 0);
    return _ArgPosition;
}

void String::PutArg(const string &aStr)
{
    if(ScanArg() == std::string::npos)
    {
        _D.append(aStr);
        return;
    }
    
    Printf<const string &>(aStr);
}

// Ce qui fait royalement chier avec les iterateurs des stl, C'est que depuis L'iterateur, comment on accede � son conteneur ???????
bool String::SkipWS(string::iterator &pos)
{
    if(_Cursor.C == _Cursor.E)
        return false;
    
    if(pos == _D.end()) // aucun moyen de savoir si L'it�rateur en est un de notre conteneur "_str" !!
        return false;
    while(isspace(*pos))
        ++pos;
    return true;
}

// Ce qui fait royalement chier avec les iterateurs des stl, C'est que depuis L'iterateur, comment on accede � son conteneur ???????
bool String::SkipWS(const char *pos)
{
    if(!pos)
        return false;
    while(pos && (*pos && isspace(*pos)))
        ++pos;
    return true;
}

string String::Word::operator()()
{
    string _s;
    if(B == E)
        _s.insert(_s.begin(), B, E + 1);
    else
        _s.insert(_s.begin(), B, E + 1);
    
    return _s;
}

std::string String::Word::operator*()
{
    string _s;
    if(B == E)
        _s.insert(_s.begin(), B, E + 1);
    else
        _s.insert(_s.begin(), B, E + 1);
    
    return _s;
    
}

std::string String::Word::Mark()
{
    String str;
    std::string::const_iterator start = B - Pos;
    
    int l = 1;
    std::string::const_iterator cc = B;
    // localiser le debut de la ligne;
    while(*cc && (cc > start) && (*cc != '\n') && (*cc != '\r'))
        --cc;
    // debut de la ligne ou de la source:
    if(cc >= start)
    {
        if((*cc == '\n') || (*cc == '\r'))
            ++cc;
        while((cc != SE) && (*cc != '\n') && (*cc != '\r'))
            str += *cc++;
    }
    String tstr;
    
    tstr << str << '\n';
    for(int x = 1; x < C; x++)
        tstr << ' ';
    tstr << '^';
    return tstr();
}

void String::Word::operator++()
{
    
}

void String::Word::operator++(int)
{
}

std::string String::Word::Location()
{
    String str = "(%d,%d)";
    str << L << C;
    return str();
}

string::const_iterator String::ScanTo(string::const_iterator start, char c)
{
    string::const_iterator p = start;
    ++p;
    while((p != _D.end()) && (*p != c))
        ++p;
    return p;
}

const char *String::ScanTo(const char *start, char c)
{
    const char *p = start;
    if(!p)
        return nullptr;
    ++p;
    while(p && (*p != c))
        ++p;
    return p;
}

/*!
    * @brief break/split/tokenize,etc... the content of this String into pieces.
    * @param wcollection  OUTPUT reference to the 'Words array' containter, filled by this method.
    * @param a_delimiters Separators in the form of a string of ascii-8 characters.
    * @param keep_as_word if true (or non-zero), the Separators will be put into the list as they appear
    * @return number of "Words/tokens" contained into the wcollection.
    * @notice : After several years of experience and experimentations, I have determined that
    * white-spaces/ctrl or spacing characters are silent and implicit delimiters, in addition to the ones supplied by \c a_delimiters.
    */
std::size_t String::Words(String::Word::Collection &wcollection, const std::string &a_delimiters, bool keep_as_word)
{
    //std::cout << __PRETTY_FUNCTION__ << ":\n";// << _D << "\n:\n";
    if(_D.empty())
    {
        std::cout << " --> Contents is Empty!";
        return (std::size_t) 0;
    }
    _Cursor.Reset(_D);
    std::string token_separators = a_delimiters.empty() ? String::_DefaultSeparators : a_delimiters;
    //std::cout << " contents after bce::Reset\n ------------- \n" << _D << "\n---------------\n: [\n" << *_Cursor.C << "\n]\n";
    if(!_Cursor.Skip())
    {
        //std::cout << " --> Contents Skip is false? (internal?)...\n";
        return (std::size_t) 0;
    }
    Word w;
    _Cursor >> w;
    
    while(!_Cursor.End())
    {
        if(!wcollection.empty());
        //std::cout << __FUNCTION__ << " last inserted Word: [" << wcollection.back()() << "] - _Cursor on [" << *_Cursor.C << "]\n";
        std::string::const_iterator cc = _Cursor.C;
        if(token_separators.find(*_Cursor.C) != string::npos)
        {
            cc = _Cursor.C;
            //std::cout << __FUNCTION__ << " Delimiter:[" << *cc << "]\n";
            if(cc > w.B)
            {
                --cc;
                wcollection.push_back({w.B, cc, _Cursor.E, w.L, w.C, w.Pos});
                //std::cout << __FUNCTION__ << ": pushed lhs Word:[" << wcollection.back()() << "];\n";
                
                _Cursor >> w;
                cc = _Cursor.C;
            }
            
            // '//' as one token instead of having two consecutive '/'
            if((*_Cursor.C == '/') && (*(_Cursor.C + 1) == '/'))
                ++_Cursor;
            
            if(keep_as_word)
            {
                wcollection.push_back({w.B, _Cursor.C, _Cursor.E, w.L, w.C, w.Pos});
                //std::cout << __FUNCTION__ << ": pushed new token:[" << wcollection.back()() << "];\n";
            }
            ++_Cursor;
            //std::cout << "        Iterator eos: " << _Cursor.End() << "\n";
            if(!_Cursor.End())
                _Cursor >> w;
            else
            {
                //std::cout << __FUNCTION__ << " - EOS: wcollection size: " << wcollection.size() << " = leaving. Done!\n";
                return wcollection.size();
            }
            
            //std::cout << " is eos?" << _Cursor.End() << "\n";
        }
        else if((*_Cursor.C == '\'') || (*_Cursor.C == '"'))
        { // Quoted litteral string...
            _Cursor >> w;
            //std::cout << __FUNCTION__ << " In quoted litteral:\n";
            if(keep_as_word)
            {
                // Create the three parts of the quoted string: (") + (litteral) + (") ( or ' )
                // So, we save the Word coords anyway.
                //std::cout << __FUNCTION__ << " Creating three parts quoted tokens: \n";
                wcollection.push_back({w.B, w.B, _Cursor.E, w.L, w.C, w.Pos});
                //std::cout << __FUNCTION__ << " 1:[" << wcollection.back()() << "]; ";
            }
            
            string::const_iterator p = ScanTo(w.B + (keep_as_word ? 0 : 1), *_Cursor.C); // w.B is the starting position, _Cursor.C is the quote delim.
            while(_Cursor.C < p)
                ++_Cursor; // compute white spaces!!!
            
            if(keep_as_word)
            {
                // then push the litteral that is inside the quotes.
                wcollection.push_back({w.B + 1, p - 1, _Cursor.E, w.L, w.C, w.Pos});
                //std::cout << " 2:[" << wcollection.back()() << "]; ";
                //++_Cursor; // _Cursor now on the closing quote
                _Cursor >> w; // Litteral is done, update w.
                wcollection.push_back({w.B, p, _Cursor.E, w.L, w.C, w.Pos});
                //std::cout << " 3:[" << wcollection.back()() << "]\n";
            }
            else
            {
                // Push the entire quote delims surrounding the litteral as the Word.
                //std::cout << __FUNCTION__ << " Creating single part quoted token: \n";
                wcollection.push_back({w.B, _Cursor.C, _Cursor.E, w.L, w.C, w.Pos});
                //std::cout << " :[" << wcollection.back()() << "]\n";
            }
            if(++_Cursor)
                _Cursor >> w;
            else
                return wcollection.size();
            
        }
        else
        {
            cc = _Cursor.C;
            ++cc;
            if(cc == _Cursor.E)
            {
                ++_Cursor.C;
                break;
            }
            //std::cout << __FUNCTION__ << " check whitespace :[" << *cc << "]\n";
            if(isspace(*cc))
            {
                if(w.B < cc)
                {
                    wcollection.push_back({w.B, cc - 1, _Cursor.E, w.L, w.C, w.Pos});
                    ++_Cursor;
                }
                
                if(_Cursor.Skip())
                {
                    _Cursor >> w;
                    continue;
                }
                return wcollection.size();
            }
            if(!_Cursor.End())
                ++_Cursor; // advance offset to the next separator/white space.
        }
    }
    if(_Cursor.C > w.B)
        wcollection.push_back({w.B, _Cursor.C - 1, _Cursor.E, w.L, w.C, w.Pos});
    
    return wcollection.size();
}


int String::Filter(const String::Collection &a_exp)
{
    if(!a_exp.size())
        return 0;
    auto i = a_exp.cbegin();
    
    // array::front is the init of the match at the beginning of this string.
    // if ...front() is Empty, then there is no required match at the beginning of this string
    // so proceed to the next substring to find.
    // if the last is not Empty, then match the last substring.
    std::string::size_type pos = 0;
    if(!(*i).empty())
    {
        //lfnl << cwhite << "must begins with [" << cyellow << (*I) << cwhite << "]:\n";
        pos = _D.find((*i));
        if(pos != 0) // no match
            return false;
    }
    else;
    //fnl << cwhite << "no requirement for the beginning\n";
    ++i;
    auto end = a_exp.cend();
    --end;
    if(!(*i).empty())
    {
        while(i < end)
        {
            if((*i).empty())
            {
                ++i;
                continue;
            }
            pos = _D.find((*i), pos);
            if(pos != std::string::npos)
            {
                ++pos;
                ++i;
                continue;
            }
            return false;
        }
    }
    if(!(*end).empty())
    {
        std::size_t sz = (*end).size();
        pos = _D.find((*end), pos);
        if(pos != std::string::npos)
        {
            if((pos + sz) != _D.size())
                return false;
        }
    }
    return true;
}

std::string String::SizeF(uint64_t sz)
{
    float fsize = (float) sz;
    String us = "";
    int currentunit = 0;
    String units[] = {"B", "kb", "mb", "gb", "tb"};
    int unitssize = sizeof(units) / sizeof(units[0]);
    
    while(fsize > 1024.0 && currentunit < unitssize - 1)
    {
        fsize /= 1024.0;
        currentunit++;
    }
    
    us = std::fixed;
    us += std::setprecision(2);
    us += fsize;
    us += " ";
    us += units[currentunit];
    
    return us;
}
std::string String::ExtractSurrounded(const std::string &first_lhs, const std::string &first_rhs)
{
    std::size_t lhs_pos = _D.find(first_lhs);
    if(lhs_pos == std::string::npos)
        return "";
    std::size_t rhs_pos = _D.find(first_rhs);
    if(rhs_pos == std::string::npos)
        return "";
    
    return _D.substr(lhs_pos, rhs_pos - lhs_pos);
}

/*!
 * @brief Try to extract the "template" type from the \c func_desc that normally shall be given by __PRETTY_FUNCTION__ at the call Location.
 *
 * template parameter assumed to be "T" ...for now.
 *
 * @param func_desc
 *
 * @note This function has no control of the proper format and (function) prototype data.
 * @return the resulting type text
 */
std::string String::TypeOf(string &&func_desc)// , const std::string& _T) -> _T is the class to search.
{
    String text = std::move(func_desc);
    String::Word::Collection w;
    
    std::size_t count = text.Words(w);
    for(auto s : w)
    {
        std::cout << s();
    }
    std::cout << '\n';
    return "finish to implement, please\n";
}



void String::ProcessArg( String::LambdaFn Fn )
{
    Format_t fmt = {_D};
    
    std::string::iterator c = _D.begin() + _ArgPosition;
    std::string::iterator n, beg, l;
    beg = n = c;
    ++c;
    // %[flag] :
    
    switch(*c)
    {
        case '-':
        case '+':
        case '#':
        case '0':fmt.F = *c++;
            break;
        default:
            //++C;
            break;
    }
    
    n = c;
    // %[width]:
    while((n != _D.end()) && isdigit(*n))
        ++n;
    l = n;
    --n;
    if(n >= c)
    {
        int t = 0;
        while(n >= c)
            fmt.W = fmt.W + (*(n--) - static_cast<uint64_t>('0')) * pow(10, t++);
    }
    else
        fmt.W = 0;
    c = l;
    
    if(*c == '.')
    {
        fmt.R = fmt.P;
        ++c;
        n = c;
        while((n != _D.end()) && isdigit(*n))
            ++n;
        l = n;
        --n;
        int t = 0;
        fmt.R = 0;
        while(n >= c)
            fmt.R = fmt.R + (*(n--) - static_cast<uint64_t>('0')) * pow(10, t++);
        c = l;
    }
    else
        fmt.R = fmt.P;
    
    //[.precision]
    n = c;
    //% ([Length]) [specifier]
    switch(*c)
    {
        case 'b':fmt.S = *c++;
            break;
        case 'd': // Decimale ou entier
        case 'i':fmt.S = *c++;
            break;
        case 'x':
        case 'X':fmt.S = *c++;
            break;
        case 'f':
        case 'F':
        case 'g':
        case 'G':fmt.S = *c++;
            break;
        case 's':fmt.S = *c++;
    }
    
    fmt.Delta = c - beg;
    //std::string ff(_D, _ArgPosition, fmt.Delta);
    _D.erase(_ArgPosition, fmt.Delta);
    _D.insert(_ArgPosition, Fn(fmt) );
    _ArgPosition = 0;
}

std::string String::Format_t::operator()()
{
    std::ostringstream str;
    str << "\nFlag    :" << F << "\n";
    str << "Width     :" << (int) W << "\n";
    str << "Precision :" << (int) P << "\n";
    str << "delta     :" << (int) Delta << "\n";
    str << "spec      :" << (char) S << "\n";
    return str.str();
}

String::BCE::BCE(const std::string &Str)
{
    B = C = Str.cbegin();
    E = Str.cend();
}

bool String::BCE::Skip()
{
    if(End())
        return false;
    
    while(isspace(*C))
    {
        switch(*C)
        {
            case 10:
            {
                if((++C) >= E)
                    return false;
                if(*C == 13)
                    ++C;
                ++L;
                Col = 1;
            }
                break;
            case 13:
            {
                if((++C) >= E)
                    return false;
                if(*C == 10)
                    ++C;
                ++L;
                Col = 1;
            }
                break;
            case '\t':++C;
                ++Col;
                break;
            default:++C;
                ++Col;
                break;
        }
    }
    return C < E;
}

bool String::BCE::End()
{
    return C >= E;
}

bool String::BCE::operator++()
{
    if(C >= E)
        return false;
    ++C;
    ++Col;
    if(C >= E)
        return false;
    return Skip();
}

bool String::BCE::operator++(int)
{
    if(C >= E)
        return false;
    ++C;
    ++Col;
    if(C >= E)
        return false;
    return Skip();
}

String::BCE &String::BCE::operator>>(String::Word &w)
{
    w.B = C;
    w.L = L;
    w.C = Col;
    w.Pos = I = (uint64_t) (C - B);
    return *this;
}
    
}
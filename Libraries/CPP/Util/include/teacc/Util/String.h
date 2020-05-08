//
// Created by Serge Lussier, lussier.serge@gmail.com, (bretzel) on 20-02-26.
//

//#ifndef UTIL_STRING_H
//#define UTIL_STRING_H

#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <time.h>
#include <cstdint>
#include <cmath>
#include <teacc/Util/Lib.h>
#include <functional>

namespace teacc::Util
{

class UTIL_LIB String
{
    static std::string __nullstr__;
    std::string _D;///< Private std::string instance.
    std::string::size_type _ArgPosition = 0; // Initialize Argument index position...
    static std::string _DefaultSeparators;
    uint8_t _Precision = 4;

private:
    // %[flags][width][.precision][Length]specifier
    struct Format_t
    {
        uint8_t F = 0; // Flag ( - + . # 0 )
        uint8_t W = 0; // Width ( Length )
        uint8_t R = 0; // Custom flag set if this format requier floating point spec.
        uint8_t P = 6; // Precision (Same as  default).
        uint8_t L = 0; // Length modifier ( L,ll,h,hh )
        std::size_t Delta = 0; // Format Length.
        std::size_t Pos = 0; //
        char S = 0; // Effective data t
        //char    _format[20]; // Unused yet.
        const char *C = nullptr;
        
        Format_t(std::string &Str) : C(Str.c_str())
        {}
        std::string operator()();
        
    };
    using LambdaFn = std::function<std::string(const String::Format_t& Fmt)>;
public:
    
    using Collection = std::vector<std::string>;
    using Iterator = Collection::iterator;
    using CIterator = Collection::const_iterator;

public:
    struct UTIL_LIB Word
    {
        std::string::const_iterator B;
        std::string::const_iterator E;
        std::string::const_iterator SE;
        
        std::string operator()();
        std::string operator*();
        
        using Collection = std::vector<Word>;
        using Iterator = Collection::iterator;
        std::string Mark();
        
        int L = 1;
        int C = 1;
        uint64_t Pos = 0;
        void operator++();
        void operator++(int);
        
        std::string Location();
    };

private:
    struct BCE
    {
        std::string::const_iterator B;
        std::string::const_iterator C;
        std::string::const_iterator E; /// ...
        
        int L = 1;
        int Col = 1;
        uint64_t I = 0;
        
        BCE() = default;
        ~BCE() = default;
        
        BCE(const std::string &Str);
        bool Skip();
        bool End();
        bool operator++();
        bool operator++(int);
        void Reset(const std::string &_str)
        {
            C = B = _str.cbegin();
            L = Col = 1;
            I = 0;
            E = _str.cend();
        }
        BCE &operator>>(Word &w);
        //BCE& operator = (const Word& w);
        
    } _Cursor;

public:
    
    String();
    String(const String &Str);
    String(String &&Str) noexcept;
    String(const std::string &aStr);
    String(std::string &&aStr);
    String(const char *aStr);
    
    ~String();
    
    String &operator=(const String &) = default;
    
    String &operator=(std::string &&aStr);
    String &operator=(String &&aStr) noexcept;
    String &operator=(const char *aStr);
    
    String &operator+=(const String &aStr);
    String &operator+=(const std::string &aStr);
    String &operator+=(char c);
    
    String &operator+(const String &aStr);
    String &operator+(const std::string &aStr);
    String &operator+(char c);
    
    template<typename t> String &operator+=(const t &a)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << a;
        _D.append(os.str());
        return *this;
    }
    
    template<typename t> String &operator+(const t &a)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << a;
        _D.append(os.str());
        return *this;
    }
    
    bool operator==(const String &aStr) const;
    
    bool Empty()
    { return _D.empty(); }
    operator bool()
    { return !_D.empty(); }
    operator std::string()
    { return _D; }
    std::string &str()
    { return _D; }
    std::string operator()() const
    { return _D; }
    
    // -- on peut maintenant commencer nos routines de manipulations et de traitements....
    static String::Collection ArgsArray(int argc, char **argv);
    String &operator<<(const String &aStr);
    String &operator<<(const char *aStr);
    String &operator<<(const std::string &aStr);
    String &operator<<(char c);
    
    bool SkipWS(std::string::iterator &pos);
    static bool SkipWS(const char *pos);
    String &operator>>(std::string &_arg);
    static std::string MakeStr(const char *B, const char *E);
    template<typename T> String &operator>>(T &_arg)
    {
        
        if constexpr (std::is_same<T, uint64_t &>::value || std::is_same<T, uint16_t &>::value || std::is_same<T, uint32_t &>::value || std::is_same<T, uint64_t &>::value || std::is_same<T, uint8_t &>::value || std::is_same<T, uint16_t &>::value || std::is_same<T, uint32_t &>::value || std::is_same<T, uint64_t &>::value)
        {
            std::string::size_type pos;
            if(((pos = _D.find("0x")) != std::string::npos) || ((pos = _D.find("0X")) != std::string::npos))
            {
                if(_D[pos] == '0')
                {
                    ++pos;
                    if((_D[pos] == 'x') || (_D[pos] == 'X'))
                    {
                        ++pos;
                        std::istringstream i(_D.c_str() + pos);
                        i >> std::hex >> _arg;
                        return *this;
                    }
                }
            }
        }
        std::istringstream in(_D); //  When String was derived from std::string ... Oops!  std::istringstream in(*this);
        in.precision(_Precision);
        in >> _arg;
        return *this;
    }
    
    char *Duplicate()
    {
        return strdup(_D.c_str());
    }
    const char *c_str()
    { return _D.c_str(); }
    void Clear();
    
    //virtual const std::string& tea_id() { return "String";}
    
    static std::string DateTime(const std::string &str_fmt);
    
    template<typename t> String &operator=(const t &_a)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << _a;
        Clear();
        _D = os.str();
        return *this;
    }
    std::string ExtractSurrounded(const std::string &first_lhs, const std::string &first_rhs);
    std::string::const_iterator ScanTo(std::string::const_iterator start, char c);
    const char *ScanTo(const char *start, char c);
    
    bool test();
    String &Oct(uint64_t __arg)
    {
        
        std::ostringstream os;
        os << std::oct << __arg;
        if(ScanArg() == std::string::npos)
        {
            _D.append(os.str());
            return *this;
        }
        
        return Printf<std::string > (os.str());
    }
    
    size_t Length()
    { return _D.size(); }
    char &operator[](size_t p)
    { return _D[p]; }
    //bool empty() { return _str.Empty(); }
    
    static std::string DefaultSeparators()
    { return String::_DefaultSeparators; }
    static std::string Separators()
    { return String::_DefaultSeparators; }
    std::size_t Words(String::Word::Collection &wcollection, const std::string &a_delimiters = "", bool keep_as_word = true);
    
    template<typename T> String &arg(T _arg)
    {
        if(ScanArg() == std::string::npos)
        {
            std::ostringstream os;
            os << std::oct << _arg;
            _D.append(os.str());
            return *this;
        }
        
        return Printf<T > (_arg);
    }
    int Filter(const String::Collection &a_exp);
    
    template<typename T> std::string Expand(const T &cnt)
    {
        String ss;
        
        int x = cnt.size();
        for(auto item : cnt)
        {
            ss << item;
            if(x-- > 1)
                ss << ',';
        }
        return ss();
    }
    
    static std::string UpperCase(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return std::toupper(c);
        });
        
        return s;
    }
    static std::string LowerCase(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        
        return s;
    }
    
    static std::string SizeF(uint64_t sz);
    
    template<typename T> String &Printf(const T &_argv);
    
    template<typename T> String &operator<<(const T &Argument)
    {
        if(ScanArg() == std::string::npos)
        {
            std::ostringstream os;
            os << Argument;
            _D += os.str();
            return *this;
        }
        
        ProcessArg([Argument](const String::Format_t& Fmt) -> std::string {
            if(Fmt.S == 'b')
            {
                bool pad = Fmt.F == '0';
                ///@todo Still have to resolve T here...
                if constexpr (
                    (!std::is_same<T,const std::string&>::value) && (!std::is_same<T, const char*>::value)
                )
                    return String::ToBinary<T>(Argument, pad, Fmt.W <= 128 ? Fmt.W : 128);
            }
            if constexpr (
                (std::is_same<T, const std::string &>::value) || (std::is_same<T, const char *>::value)
            )
                return Argument;
    
            std::ostringstream os;
            os << Argument;
            return os.str();
        });
        return *this;
    }
    
    template<typename T> String &Hex(T &v)
    {
        std::stringstream is(_D.c_str() + 2);
        //std::cerr << " this:'" << _D.c_str()+2 << "' -> ";
        is >> std::hex >> v;
        //std::cerr << v << '\n';
        return *this;
    }
    
    static std::string TypeOf(std::string &&func_desc);
    
    template<typename T> static std::string ToBinary(T __arg, bool padd = false, int f = 128)
    {
        uint8_t seq;
        int nbytes = sizeof(T);
        
        uint8_t tableau[sizeof(T)];
        memcpy(tableau, (uint8_t *) &__arg, nbytes);
        std::string stream = "";
        int s = 0;
        //bool discard = false;
        for(int x = 1; x <= nbytes; x++)
        {
            seq = tableau[nbytes - x];
            if((x == 1 && !padd && !seq) || (stream.empty() && !padd && !seq))
                continue;
            for(int y = 7; y >= 0; y--)
            { // est-ce que le bit #y est � 1 ?
                if(s >= f)
                {
                    stream += ' ';
                    s = 0;
                }
                ++s;
                uint8_t b = 1 << y;
                if(b & seq)
                    stream += '1';
                else
                    stream += '0';
            }
        }
        /*tableau.Clear();*/
        return stream;
    }
    
    std::string::const_iterator Begin(){ return _D.begin();}
    std::string::const_iterator End()  { return _D.end(); }

private:
    std::string::size_type ScanArg();
    void ProcessArg(String::LambdaFn Fn);
    
    void PutArg(const std::string &aStr);
    int PushWord(Word::Collection &strm, Word &w, std::string::size_type sz);
    
};

template<typename T> String &String::Printf(const T &_argv)
{
    Format_t fmt = {_D};
    char buf[256];
    std::memset(buf, 0, 200);
    //LFnl << "\n";


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
            //++M;
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
    std::string BinaryStr;
    switch(*c)
    {
        case 'b':
        {
            if constexpr (!std::is_same<T, const std::string &>::value)
            {
                // Special Bretzelus :
                bool pad = fmt.F == '0';
                BinaryStr = String::ToBinary<T>(_argv, pad, fmt.W <= 128 ? fmt.W : 128);

                //std::sprintf(buf, "%s", BinaryStr.c_str());
                fmt.Delta = (c + 1) - beg;
                _D.erase(_ArgPosition, fmt.Delta);
                _D.insert(_ArgPosition, BinaryStr.c_str(), BinaryStr.length());
                _ArgPosition = 0;
                return *this;
            }
        }

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
    std::string ff(_D, _ArgPosition, fmt.Delta);

    // -- Clang-tidy:error: cannot pass object of non-trivial type 'const std::__cxx11::basic_string<char>' through variadic function
    //
    if constexpr (std::is_same<T, const std::string &>::value)
        std::snprintf(buf, 199, ff.c_str(), _argv.c_str());
    else
        std::sprintf(buf, ff.c_str(), _argv);

    _D.erase(_ArgPosition, fmt.Delta);
    _D.insert(_ArgPosition, buf, std::strlen(buf));
    _ArgPosition = 0;
    return *this;
};

}
//#endif //LIBXIO_String_H
//plsc : Poor LoneSome Coder. Then LoneSome Coder.
// FUCKING CMAKE BUG FUCK THE FUCK!!!!!!!!!!!!!


//
// Created by bretzel on 20-04-17.
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


namespace teacc::Util
{

class PUBLIC_LIB String
{
    static std::string __nullstr__;
    std::string _D;///< Private std::string instance.
    std::string::size_type _ArgPos = 0; // Initialize Argument index position...
    static std::string _DefaultSeparators;
    uint8_t _Precision = 4;

public:
    using Collection = std::vector<std::string>;
    using Iterator = Collection::iterator;
    using CIterator = Collection::const_iterator;
    
    struct PUBLIC_LIB  Word
    {
        String::CIterator B;
        String::CIterator E;
        String::CIterator SE;
        int L = 1;
        int C = 1;
        uint64_t Pos = 0;
        
        using Collection = std::vector<String::Word>;
        using Cursor_t = Collection::iterator;
        
        std::string Mark();
        
        void operator++();
        void operator++(int);
        std::string operator()();
        std::string operator*();
        std::string Location();
    };

private:
    struct BCE
    {
        std::string::const_iterator B;
        std::string::const_iterator C;
        std::string::const_iterator E; /// ...
        
        int L       = 1;
        int COL     = 1;
        uint64_t I  = 0;
        
        BCE() = default;
        ~BCE() = default;
        
        BCE(const std::string &ARef);
        bool Skip();
        bool End();
        bool operator++();
        bool operator++(int);
        void Reset(const std::string &Str)
        {
            C = B = Str.cbegin();
            L = COL = 1;
            I = 0;
            E= Str.cend();
        }
        BCE &operator>>(Word &w);
        //_bce& operator = (const word& w);
        
    } _Cursor;
    
public:
    String() = default;
    ~String() = default;
    
    #pragma region COPY_AND_MOVE
    // Copy & Move:
    String(const String& Str);
    String(String&& Str) noexcept;
    String& operator =(const String &Str);
    String& operator =(String &&Str) noexcept;
    String& operator +=(const String &Str);
    String &operator +=(String &&Str) noexcept;
    // ---------------------------------------
    #pragma endregion COPY_AND_MOVE
    
    #pragma region DETAILS
    std::string operator()()
    {
        return _D;
    }
    
    #pragma endregion DETAILS
    
    #pragma region ASSIGN
    //Assign
    template<typename T> String& operator=(const T& Val)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << Val;
        _D = os.str();
        return *this;
    }
    
    template<typename T> String &operator=(T &&Val) noexcept
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << std::move(Val);
        _D = os.str();
        return *this;
    }
    
    template<typename T> String &operator+=(const T &Val)
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << Val;
        _D.append(os.str());
        return *this;
    }
    
    template<typename T> String &operator+=(T &&Val) noexcept
    {
        std::ostringstream os;
        os.precision(_Precision);
        os << std::move(Val);
        _D.append(os.str());
        return *this;
    }
    // -------------------------------------------
    #pragma endregion ASSIGN
    
    #pragma region APPEND
    template<typename T> std::string operator +(const T& Val)
    {
        String Str = Val;
        return _D + Str();
    }
    #pragma endregion APPEND
    
    #pragma region TOKENS
    bool SkipWS(std::string::iterator &pos);
    //static bool SkipWS(const char *pos);
    std::string DefaultSeparators(){ return String::_DefaultSeparators; }
    std::size_t Tokenize(String::Word::Collection &Container, const std::string &Delimiters = "", bool KAW = true);
    #pragma endregion TOKENS
    
};

}

//#endif //UTIL_STRING_H

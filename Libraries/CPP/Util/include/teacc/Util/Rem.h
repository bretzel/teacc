#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by bretzel on 20-04-18.
//

//#ifndef UTIL_REM_H
//#define UTIL_REM_H

#pragma once

#include <teacc/Util/String.h>
#include <stack>
//#include <functional> // Already loaded from String.h
#include <any>  // Used by the Expect template class.

namespace teacc::Util
{

class UTIL_LIB Rem
{
    
    std::string mText;
    String::Collection mVerticalData;
    
public:
    
    enum class Int: uint8_t
    {
        Ok = 0,
        Fail,
        Eof,
        Eos,
        Eot,
        UnExpected,
        Expected,
        Null,
        Bad,
        Good,
        Unknown,
        Known,
        Unset,
        UnInit,
        Implement,
        Accepted,
        Rejected,
        Unterminated
    };
    
    enum class Type : uint8_t
    {
        None = 0,
        Info,
        Internal,
        Error,
        SyntaxError,
        Warning,
        Fatal,
        Success,
        Message,
        Return,
        Value,
        State,
        Debug
        
    };
private:
    
    Type mType = Rem::Type::None;
    Int  mCode = Rem::Int::Unknown;
    
    using RemStack = std::stack<Rem>;
    static RemStack _Stack;
    
    static Rem      _Null;
public:
    
    
    Rem() = default;
    ~Rem();
    
    Rem(const Rem& R) = default;
    Rem(Rem && R) noexcept;
    
    Rem& operator = (const Rem& R) = default;
    Rem &operator = (Rem &&R) noexcept;
    
    std::string Text();
    std::string operator()();
    
    explicit operator bool() const;
    
    static Rem& Save();
    static Rem& Get();
    
    static Rem& Null();
    
    
    static std::string ToStr(Rem::Type T);
    static std::string ToStr(Rem::Int C);
    
    
    
    Rem& operator << (Rem::Type T);
    Rem& operator << (Rem::Int C);
    
    template<typename T> Rem& operator << (const T& Arg)
    {
        String Str = mText;
        Str << Arg;
        mVerticalData.push_back(Str());
        return *this;
    }
    
    static std::size_t Clear(std::function<void(Rem&)> LambdaFN=nullptr);
};


template<typename T = Rem::Int> class Expect
{
    std::any mVal;
    bool     mF = false;

public:
    Expect() = default;
    
    Expect(Rem &R)
    {
        mVal = R; // new notification();
        mF = false;
    }
    
    Expect(const T &V)
    {
        mVal = V; // Must remove const ?
        mF   = true;
    }
    
    Expect(Expect && E) noexcept
    {
        mVal = std::move(E.mVal);
        mF = E.mF;
    }
    
    Expect(const Expect &E)
    {
        mF = E.mF;
        mVal = E.mVal;
    }
    
    Expect &operator=(Rem &R)
    {
        mVal.reset();
        mF = false;
        mVal = R;
        return *this;
    }
    
    Expect &operator=(Expect &&E) noexcept
    {
        mVal.reset();
        mVal = std::move(E.mVal);
        mF = std::move(E.mF);
        
        return *this;
    }
    
    Expect &operator=(const Expect &E)
    {
        if(&E == this)
            return *this;
        mVal.reset();
        mVal = E.mVal;
        mF = E.mF;
        return *this;
    }
    
    Expect &operator=(const T &V)
    {
//        /if(mF)
        mVal.reset();
        mVal = V;
        mF = true;
        return *this;
    }
    
    explicit operator bool() const
    { return mF; }
    
    Rem & operator ()()
    {
        if(mF)
            return Rem::Null();
        return std::any_cast<Rem &>(mVal);
    }
    
    auto &operator*()
    {
        if(!mF)
        {
            Rem::Save() <<  Rem::Type::Error <<  ": " << __PRETTY_FUNCTION__ <<  " - Expected value was not returned. >>\n >> " <<
            std::any_cast<Rem>(mVal).operator()();
            
            mVal.reset();
            mVal = T(); // Yep... T must be default-constructible...
        }
        return std::any_cast<T &>(mVal);
    }
    
//    auto &operator()()
//    {
//        if(!f)
//        {
//            _a = notification::push(), "expect: expected value on a false state.";
//            return std::any_cast<notification &>(_a);
//        }
//        return std::any_cast<T &>(_a);
//    }
    
    void Reset()
    {
        mVal.reset();
        mF = false;
    }
    
    ~Expect()
    {
        //Reset();
    }
    /*!
        @brief  to be verified.
    */
    std::string Text(std::function<std::string(const T &)> textify_ = nullptr)
    {
        if(*this)
        {
            String Str;
            std::string rr;
            T &v = *(*this);
            if(textify_)
                return textify_(v);
            else
            {
                Str << __PRETTY_FUNCTION__;
                rr = Str.ExtractSurrounded("T =", ";");
                Str = " No method given, for textifying this instance of Expect<T>:[";
                Str << rr << ']';
            }
            return Str();
        }
        return std::any_cast<Rem &>(mVal)();
    }
};

}

//#endif //UTIL_REM_H

#pragma clang diagnostic pop
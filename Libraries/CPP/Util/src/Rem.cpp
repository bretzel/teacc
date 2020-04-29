//
// Created by bretzel on 20-04-18.
//

#include <teacc/Util/Rem.h>
#include <map>


using namespace teacc::Util;

Rem::RemStack Rem::_Stack;
Rem  Rem::_Null;

Rem::Rem(Rem &&R) noexcept
{
    mText = std::move(R.mText);
    mVerticalData = std::move(R.mVerticalData);
    mType = R.mType;
    mCode = R.mCode;
}


Rem &Rem::operator=(Rem &&R) noexcept
{
    mText = std::move(R.mText);
    mVerticalData = std::move(R.mVerticalData);
    mType = R.mType;
    mCode = R.mCode;
    
    return *this;
}
std::string Rem::Text()
{
    return mText;
}

std::string Rem::operator()()
{
    mText.clear();
    if(mVerticalData.empty())
        return "empty"; // ?
    
    for(auto &R : mVerticalData)
    {
        mText += R;
        mText += ' ';
    }
    return mText;
}


Rem::operator bool() const
{
    return mType != Type::None;
}

Rem &Rem::Save()
{
    Rem::_Stack.push(Rem());
    return Rem::_Stack.top();
}

Rem &Rem::Get()
{
    if(Rem::_Stack.empty())
        return Rem::_Null;
    
    Rem& R = Rem::_Stack.top();
    Rem::_Stack.pop();
    return R;
}


Rem &Rem::Null()
{
    return Rem::_Null;
}


std::size_t Rem::Clear(std::function<void(Rem &)> LambdaFN)
{
    std::size_t Sz = Rem::_Stack.size();
    if(!Sz)
        std::cout << " No Rem to clear.\n";
    while(!Rem::_Stack.empty())
    {
        if(LambdaFN)
            LambdaFN(Rem::_Stack.top());
        Rem::_Stack.pop();
    }
    
    return Sz;
}

std::string Rem::ToStr(Rem::Type T)
{
    
    std::map<Rem::Type, std::string> _ = {
        {Rem::Type::None,    "None"},
        {Rem::Type::Info,    "Info"},
        {Rem::Type::Internal,"Internal"},
        {Rem::Type::Error,   "Error"},
        {Rem::Type::SyntaxError, "Syntax Error"},
        {Rem::Type::Warning, "Warning"},
        {Rem::Type::Fatal,   "Fatal"},
        {Rem::Type::Success, "Success"},
        {Rem::Type::Message, "Message"},
        {Rem::Type::Return,  "Return"},
        {Rem::Type::Value,   "Value"},
        {Rem::Type::State,   "State"},
        {Rem::Type::Debug,   "Debug"}
    };
    return "Rem::" + _[T];
}


std::string Rem::ToStr(Rem::Int C)
{
    std::map<Rem::Int, std::string> _ = {
        {Rem::Int::Ok,          "Ok"},
        {Rem::Int::Fail,        "Fail"},
        {Rem::Int::Eof,         "Eof"},
        {Rem::Int::Eos,         "Eos"},
        {Rem::Int::Eot,         "Eot"},
        {Rem::Int::UnExpected,  "UnExpected"},
        {Rem::Int::Expected,    "Expected"},
        {Rem::Int::Null,        "Null"},
        {Rem::Int::Bad,         "Bad"},
        {Rem::Int::Good,        "Good"},
        {Rem::Int::Unknown,     "Unknown"},
        {Rem::Int::Known,       "Known"},
        {Rem::Int::Unset,       "Unset"},
        {Rem::Int::UnInit,      "UnInit"},
        {Rem::Int::Implement,   "Not Implemented"},
        {Rem::Int::Accepted,    "Accepted"},
        {Rem::Int::Rejected,    "Rejected"},
    };
    
    return _[C];
}

Rem &Rem::operator<<(Rem::Type T)
{
    mVerticalData.push_back(ToStr(T));
    return *this;
}

Rem &Rem::operator<<(Rem::Int C)
{
    mVerticalData.push_back(ToStr(C));
    return *this;
}
Rem::~Rem()
{
    mVerticalData.clear();
    mText.clear();
}


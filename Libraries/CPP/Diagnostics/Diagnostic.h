//
// Created by bretzel on 20-04-21.
//

//#ifndef UTIL_DIAGNOSTIC_H
//#define UTIL_DIAGNOSTIC_H

#pragma once

#include <teacc/Util/Rem.h>
#include <map>

namespace teacc
{

class TestBase
{
public:
    virtual Util::Expect<> Run(Util::String::Collection Args_) = 0;
};



template<typename T> class Test : public TestBase
{
    using Collection = std::map<std::string, TestBase*>;
    T*  mClass = nullptr;
    Util::String::Collection mArgs;
public:
    Test() = default;
    Test(const Test&) = default;
    Test(Test&&) = default;
    ~Test() = default;
    
    Util::Expect<> Run(Util::String::Collection Args_) override
    {
        mArgs = std::move(Args_);
        return Util::Rem::Int::Implement;
    }
    
};


class Diagnostic
{
    using Collection = std::vector<TestBase*>;
    
    Collection mTests;
    std::string mName;
public:
    // -- Let's see and learn:
    Diagnostic() = default;
    Diagnostic(const Diagnostic&) = default;
    Diagnostic(Diagnostic&&) = default;
    Diagnostic& operator=(Diagnostic&&) noexcept = default;
    Diagnostic& operator=(const Diagnostic&) = default;
    //------------------------
    
    Diagnostic(std::string Name_);
    ~Diagnostic();
    
    Util::Expect <> Run(Util::String::Collection Args_);
    
    
    


};
}


//#endif //UTIL_DIAGNOSTIC_H

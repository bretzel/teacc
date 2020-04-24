//
// Created by bretzel on 20-04-21.
//

//#ifndef UTIL_DIAGNOSTIC_H
//#define UTIL_DIAGNOSTIC_H

#pragma once

#include <teacc/Util/Rem.h>
#include <map>

namespace Diag
{

using namespace teacc::Util;



class Test
{
    using Collection = std::map<std::string, Test*>;
    String::Collection mArgs;
    std::string mName;
public:
    Test() = default;
    Test(std::string Name_);
    Test(const Test&) = default;
    Test(Test&&) = default;
    ~Test() = default;
    
    virtual Expect<> Run() = 0;
};


class Diagnostic
{
    using Collection = std::vector<Test*>;
    
    Collection mTests;
    String::Collection mTestsName;
    std::string mName;
    std::size_t Init();
    
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
    
    Expect <> Run(String::Collection Names_);
    
};
}


//#endif //UTIL_DIAGNOSTIC_H

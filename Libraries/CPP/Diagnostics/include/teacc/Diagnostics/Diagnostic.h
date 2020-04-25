//
// Created by bretzel on 20-04-21.
//


#pragma once
#include <teacc/Diagnostics/Lib.h>
#include <teacc/Util/Rem.h>
#include <map>

using namespace teacc::Util;

namespace Diag
{


class DIAGNOSTIC_LIB Test
{
    using Collection = std::map<std::string, Test*>;
    String::Collection mArgs;
    std::string mName;
    friend class Diagnostic;
public:
    
    struct DiagnosticData
    {
        using Collection = std::vector<DiagnosticData>;
        using Iterator   = Collection::iterator;
        
        std::string mName;
        Expect<> mResult = Rem::Int::Unset;
        
        std::string operator()();
    };
    
    Test() = default;
    Test(std::string Name_);
    Test(const Test&) = default;
    Test(Test&&) = default;
    ~Test() = default;
    
    std::string Name() { return mName; }
    virtual Expect<> Run() = 0;
};


class DIAGNOSTIC_LIB Diagnostic
{
    Test::Collection mTests; ///< Reference Tests
    std::stack<Test*> mToRun; ///< Stacked Tests
    String::Collection mTestsNameToRun;
    std::string mName;
    
protected:
    
    using TestCreateFn = std::function<Test*(std::string)>;
    
    std::size_t Init(Diagnostic::TestCreateFn Fn = nullptr);
    
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


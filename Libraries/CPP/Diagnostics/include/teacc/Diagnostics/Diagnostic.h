//
// Created by bretzel on 20-04-21.
//


#pragma once
#include <teacc/Diagnostics/Lib.h>
#include <teacc/Util/Rem.h>
#include <map>

using namespace teacc::Util;

namespace DTest
{

struct DiagnosticData
{
    
    using Collection = std::map<std::string, DiagnosticData>;
    using RunFN_t    = std::function<Expect<>(String::Collection)>;
    std::string      mName;
    std::string      mCmdLine;
    String::Collection mArgs; //Broken mCmdLine into std::string whitespace-separated components.
    String::Word::Collection mWords; // Broken mArgs into meaningful final Token components, excluding mArgs[0] which is the '--Test'$Name'.
    
    Expect<> mResult = Rem::Int::Unset;
    
    RunFN_t mRunFn = nullptr;
    DiagnosticData() = default;
    DiagnosticData(const DiagnosticData& D) = default;
    DiagnosticData(DiagnosticData&& D) = default;
    
    DiagnosticData(std::string Name_, RunFN_t F)
    {
        mName = std::move(Name_);
        mRunFn = F;
    }
    
    DiagnosticData& operator=(const DiagnosticData&) = default;
    DiagnosticData& operator=(DiagnosticData&&) = default;
    
    DiagnosticData& operator << (std::string Arg_)
    {
        mArgs.push_back(std::move(Arg_));
        return *this;
    }
    
    Expect<> operator()();
    
private:
    std::size_t ProcessCmdLine();
    
};



struct TestData{
    std::string Name;
    DiagnosticData::RunFN_t Fn;
};

class DIAGNOSTIC_LIB Diagnostic
{
    DiagnosticData::Collection mData; ///< Reference Tests
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
    
    Expect <> Run(String::Collection Names_);
    Diagnostic& operator << (TestData&& D);
    
private:
    auto Seek(const std::string& CI);
    
    std::size_t Map(String::Collection Args_);
};
}


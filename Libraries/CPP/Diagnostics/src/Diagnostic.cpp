//
// Created by bretzel on 20-04-21.
//


#include <teacc/Diagnostics/Diagnostic.h>

namespace DTest
{

Diagnostic::Diagnostic(std::string Name_) : mName(std::move(Name_))
{}

Diagnostic::~Diagnostic()
{
    mName.clear();
}

Expect<> Diagnostic::Run(String::Collection Args_)
{
    Expect<> R;
    int C = 0;
    std::cout << "\n------------------------------ DIAGNOSTICS TESTS --BEGIN-------------------------------\n\n";
    for(auto const& S : Args_)
    {
        if(C++)
            std::cout << "\x1b[32mTest \x1b[1;35mCmdLineArg#\x1b[1;34m" << C-1 << "\x1b[1;37m: " << S << "\x1b[0m\n";
    }
    std::cout << Map(std::move(Args_)) << " mapped Command Line Args.\n";
    
    std::cout << " Running Tests:\n";
    for(auto Ti:mData)
    {
        if( !Ti.second.mCmdLine.empty() ) (Ti.second)();
        else
            Rem::Save() << Rem::Type::Warning << ": " << " Test [" << Ti.first << "] ignored";
    }
    Rem::Clear( [](Rem& R) {std::cout << R() << '\n';} );
    std::cout << "\n-------------------------- END DIAGNOSTICS TESTS --------------------------------------\n\n\n\n";
    
    return Rem::Int::Ok;
}


Diagnostic &Diagnostic::operator<<(TestData&& D)
{
    mData[D.Name] = DiagnosticData(D.Name, D.Fn);
    return *this;
}


auto Diagnostic::Seek(const std::string& CI)
{
    auto Ti = mData.begin();
    while(Ti != mData.end())
    {
        if(std::size_t n = CI.find(Ti->first); n != std::string::npos) break;
        Ti++;
    }
    if(Ti==mData.end())
        Rem::Save() << Rem::Type::Message << " Argument Line [\x1b[31m" << CI <<"\x1b[0m] is ignored";
    
    return Ti;
}

/*!
 *  @brief Maps CmdLine Args ( From the CMake custom target script which has a specific Quoting enforcement )
 *
 *  @return number of prepared tests.
 *
 *  @note Do NOT invoke these tests diagnostics from the cmdline shell! This library is NOT made to be used in the terminal shell! You've been warned!
 *
 *  @author &copy; 2020, Serge Lussier (lussier.serge@gmail.com); LoneSomeCoder; Bretzelus; Bretzel; Dynalog.
 */
std::size_t Diagnostic::Map(String::Collection Args_)
{
    // Main Loop
    std::cout << "Mapping Commandline Line with DiagnosticData Objects by name:\n";
    if(mData.empty())
    {
        Rem::Save() << Rem::Type::Error << " Diagnostic::Map : No Diagnostics/Tests data set.\n -- Aborting Diagnostics.";
        return 0;
    }
    
    int C=0;
    for(auto const& CI : Args_)
    {
        if(!C++) continue;
        if(auto Ti = Seek(CI); Ti != mData.end())
        {
            Ti->second.mCmdLine = CI;
            std::cout << Ti->second.mName << "\n    => Associated ArgumentLine[\x1b[1;32m" << Ti->second.mCmdLine << "\x1b[0m]\n";
        }
    }
    std::cout << "--------------------------------------------------------------------------\n";
    return mData.size();
}

Expect<> DiagnosticData::operator()()
{
    String Str = mCmdLine;
    ProcessCmdLine();
    std::size_t sz = Str.Words(mWords, String::DefaultSeparators(), true);
    if(sz)
    {
        for(auto  W:mWords)
        {
            std::cout << "[" << W() << "] ";
        }
        std::cout << "\n";
    }
    return (mRunFn ? mRunFn(mArgs) : Rem::Int::Unset);
}


std::size_t DiagnosticData::ProcessCmdLine()
{
    std::cout << __PRETTY_FUNCTION__ << ": '" << mCmdLine << "' \\O/\n";
    return 0;
}

}//namespace DTest;



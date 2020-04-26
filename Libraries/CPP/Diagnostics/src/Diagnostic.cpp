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
    int C = 1;
    std::cout << "Mapping Args with DiagnosticData Objects by name:\n";
    auto count = Map(std::move(Args_));
    std::cout << count << '\n';
    
    return Rem::Int::Ok;
}


Diagnostic &Diagnostic::operator<<(TestData&& D)
{
    mData[D.Name] = DiagnosticData(D.Name, D.Fn);
    return *this;
}
String::CIterator Diagnostic::Seek(const std::string &Name_, const String::Collection &Args_)
{
    auto CI = Args_.cbegin();
    ++CI; // Skip Arg:0.
    
    while(CI != Args_.cend())
    {
        if(std::size_t n = CI->find(Name_); n != std::string::npos) break;
        ++CI;
    }
    return CI;
}


/*!
 *  @brief Maps CmdLine Args ( From the CMake custom target script which has a specific Quoting enforcement )
 *
 *  @return number of prepared tests.
 *
 *  @note Do NOT invoke these tests diagnostics from the cmdline shell! This library is NOT made to be used the terminal shell! You've been warned!
 *
 *  @author &copy; 2020, Serge Lussier (lussier.serge@gmail.com); LoneSomeCoder; Bretzelus; Bretzel; Dynalog.
 */
std::size_t Diagnostic::Map(String::Collection Args_)
{
    // Main Loop
    if(mData.empty())
    {
        Rem::Save() << Rem::Type::Error << " Diagnostic::Map : No Diagnostics/Tests data set.\n -- Aborting Diagnostics.";
        return 0;
    }
    
    for(auto Ti : mData)
    {
        if(auto CI = Seek(Ti.first, Args_); CI != Args_.cend())
        {
            Ti.second.mCmdLine = *CI;
            std::cout << Ti.second.mName << "\n    => Associated ArgumentLine[\x1b[1;32m" << Ti.second.mCmdLine << "\x1b[0m]\n";
            
            String Str = *CI;
            String::Word::Collection Words;
            std::cout << " Test: String::Words on CmdLineArg :";
            std::size_t count = Str.Words(Words, String::DefaultSeparators(), true);
            std::cout << count << " words:\n";
            for(auto W : Words)
            {
                std::cout << "[" << W() << "]\n";
            }
        }
        std::cout << "--------------------------------------------------------------------------\n";
    }
    return 0;
}

}//namespace DTest;



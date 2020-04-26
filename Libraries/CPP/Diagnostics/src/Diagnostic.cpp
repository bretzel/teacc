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
    for(auto Ti : mData)
    {
        if(auto CI = Seek(Ti.first, Args_); CI != Args_.cend())
        {
            Ti.second.mCmdLine = *CI;
            std::cout << Ti.second.mName << "\n    => Associated ArgumentLine[\x1b[1;32m" << Ti.second.mCmdLine << "\x1b[0m]\n";
        }
    }
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
    while(CI != Args_.end())
    {
        if(std::size_t n = CI->find(Name_); n != std::string::npos) break;
        ++CI;
    }
    return CI;
}


}//namespace DTest;



//
// Created by bretzel on 20-04-18.
//

//#include <teacc/Util/String.h>
#include "UtilTests.h"
#include <teacc/Util/AppBook.h>

using namespace teacc::Util;
using teacc::AppBook;


auto main(int argc, char**argv) -> int
{
    
    UtilTests Test;
    std::cout << "UtilTests::Run : \n";
    auto E = Test.Run(argc, argv);
    std::cout << Rem::ToStr(*E) << '\n';
    // ...
    
    return 0;
}

using namespace teacc::Util;


UtilTests::~UtilTests()
{

    Rem::Clear([](Rem& R) {
       std::cout <<  R() << '\n';
    });

}


Expect<> UtilTests::Init(int argc, char **argv)
{
    mDiagnostics.push_back({"Init", Rem::Int::UnInit});
    DiagnosticData &Dia = mDiagnostics.back();
    
    String::Collection Args = String::ArgsArray(argc, argv);
    int c = 0;
    for(auto S : Args)
    {
        std::cout << c << ": " << S << '\n';
    }
    Dia.mResult = Rem::Int::Implement;
    return {(
        Rem::Save() << Rem::Type::Debug << Rem::Int::Implement << __PRETTY_FUNCTION__ << ": Start."
    )};
    
}

Expect<> UtilTests::TestAppBook()
{
    mDiagnostics.push_back({"AppBook"});
    DiagnosticData &Dia = mDiagnostics.back();
    
    AppBook::Config() ={
        "Teacc :: Util :: Tests.",
        "UtilTests.log",
        AppBook::Ansi
    };
    AppBook::Init();
    AppBook::Log& Log = AppBook::Begin(AppBook::Info);
    
    Log << "Hello!" << AppBook::Color::DarkSeaGreen1  << AppBook::Eol;
    Log.End();
    AppBook::End();
    
    Dia.mResult = Rem::Int::Ok;
    return Dia.mResult;
}


Expect<> UtilTests::Run(int argc, char **argv)
{
    mDiagnostics.push_back({ "Run"});
    DiagnosticData &Dia = mDiagnostics.back();
    
    
    Init(argc, argv); // E is expected to be "false";
    TestAppBook();
    TestString();
    
    Dia.mResult = Rem::Int::Ok;
    
    for(auto D : mDiagnostics)
    {
        std::cout << D() << '\n';
    }
    return Rem::Int::Ok;
}

std::string UtilTests::DiagnosticData::operator()()
{
    
    return mName + ": " + (
        mResult ? Rem::ToStr(*mResult) :
        mResult()()
    );
}

Expect<> UtilTests::TestString()
{
    mDiagnostics.push_back({"String"});
    DiagnosticData &Dia = mDiagnostics.back();
    
    String Str = "Hello, World!\n ==> This is the VeryFirst of the %s Tests!\n----------------------------------------------------------\n";
    Str << " teacc::Util Library";
    std::cout << Str();
    
    Dia.mResult = Rem::Int::Ok;
    return Dia.mResult;
}

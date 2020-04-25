//
// Created by bretzel on 20-04-21.
//


#include "../include/teacc/Diagnostics/Diagnostic.h"
#include "../UtilTests.h"



namespace Diag
{

Diagnostic::Diagnostic(std::string Name_) : mName(std::move(Name_))
{}

Diagnostic::~Diagnostic()
{
    mName.clear();
}

Expect<> Diagnostic::Run(String::Collection Args_)
{
    mTestsNameToRun = std::move(Args_);
    Init();
    Expect<> R;
    while(!mToRun.empty())
    {
        ///@todo Open Output.
        Test* Test_ = mToRun.top();
        if((R = Test_->Run()))
            Rem::Save() << Test_->Name() << ":-> " << Rem::ToStr(*R);
        
        ///@todo Close Output.
        mToRun.pop();
    }
    return Rem::Int::Ok;
}


/*!
 * @brief Create and Initialize the tests by the names given in the Args_ Collection.
 * @return
 */
std::size_t Diagnostic::Init(Diagnostic::TestCreateFn Fn)
{
//    mTests = {
//        {"Util", new UtilTests("Util")}
//    };
    
    std::cout << "Stacking:\n";
    if(!Fn)
    {
        Rem::Save() << __PRETTY_FUNCTION__ << "\n" << Rem::Type::Fatal << ": No Test-Instanciate function was provided.\nDiagnostics Tests aborted.";
        return 0;
    }
    
    int C = 0;
    for(auto Name : mTestsNameToRun)
    {
        if(C++)
        {
            std::cout << "Test #" << C-1 << " :[" << Name << "]\n";
            if(Fn)
                mToRun.push(mTests[Name] = Fn(Name));
            else
                Rem::Save() << Rem::Type::Error <<
                Rem::Int::Bad << " Name: Test identified by '" <<
                Name << "' was rejected.";
        }
    }
    
    return mToRun.size();
}


Test::Test(std::string Name_): mName(std::move(Name_)){}

}//namespace Diag;



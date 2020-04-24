//
// Created by bretzel on 20-04-21.
//


#include "Diagnostic.h"

#include "UtilTests.h"



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
        {
            Rem::Save() << Test_->Name() << ":-> " << Rem::ToStr(*R);
        }
        else
            R = (
                Rem::Save() << Test_->Name() << ":-> " << R()()
            );
        ///@todo Close Output.
        mToRun.pop();
    }
    
    return Rem::Int::Ok;
}


/*!
 * @brief Create and Initialize the tests by the names given in the Args_ Collection.
 * @return
 */
std::size_t Diagnostic::Init()
{
    mTests = {
        {"Util", new UtilTests("Util")}
    };
    
    std::cout << "Stacking:\n";
    int C = 0;
    for(auto Name : mTestsNameToRun)
    {
        if(C++)
        {
            std::cout << "Test #" << C-1 << " :[" << Name << "]\n";
            mToRun.push(mTests[Name]);
        }
        
        
    }
    
    return mToRun.size();
}


Test::Test(std::string Name_): mName(std::move(Name_)){}

}//namespace Diag;


auto main(int argc, char **argv)->int
{
    Diag::Diagnostic D = {"teacc"};
    teacc::Util::String::Collection Args = teacc::Util::String::ArgsArray(argc,argv);
    D.Run(Args);
    teacc::Util::Rem::Clear([](teacc::Util::Rem& R)
    {
        std::cout << R() << '\n';
    }
    );
    return 0;
}


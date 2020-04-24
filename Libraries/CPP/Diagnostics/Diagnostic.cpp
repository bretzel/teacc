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
    mTestsName = std::move(Args_);
    Init();
    Expect<> R;
    for(auto *Test_ : mTests)
    {
        ///@todo Open Output.
        if((R = Test_->Run())
        {
            Rem::Save() << Test_.Name() << ":-> " << Rem::ToStr(*R);
        }
        
        ///@todo Close Output.
    }
    
    return Rem::Int::Implement;
}


/*!
 * @brief Create and Initialize the tests by the names given in the Args_ Collection.
 * @return
 */
std::size_t Diagnostic::Init()
{
    for(auto Name : mNames)
}

auto main(int arc, char **argv)->int
{
    return 0;
}


Test::Test(std::string Name_): mName(std::move(Name_))
{

}


}
//
// Created by bretzel on 20-04-21.
//


#include "Diagnostic.h"

#include <teacc/Util/String.h>

using namespace teacc;
using Util::Rem;
using Util::Expect;

Diagnostic::Diagnostic(std::string Name_):mName(std::move(Name_)){}

Diagnostic::~Diagnostic()
{
    mName.clear();
}

Expect<> Diagnostic::Run(Util::String::Collection Args_)
{
    for(auto* Test_ : mTests)
    {
        ///@todo Open Output.
        Test_->Run(Args_);
        ///@todo Close Output.
    }
    
    return Rem::Int::Implement;
}

auto main(int arc, char**argv) -> int
{
    return 0;
}

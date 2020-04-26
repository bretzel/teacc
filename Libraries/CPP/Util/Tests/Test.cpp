//
// Created by bretzel on 20-04-25.
//

#include "Test.h"


using teacc::Util::String;
using teacc::Util::Rem;
using teacc::Util::Expect;

Expect<> Test_String_Words(String::Collection Args)
{
    return Rem::Int::Implement;
}


auto main(int argc, char** argv) -> int
{
    String::Collection Args = String::ArgsArray(argc, argv);
    int C=0;
    for(auto S : Args)
    {
        if(C++)
            std::cout << "\x1b[32mTest \x1b[1;35mCmdLineArg#\x1b[1;34m" << C-1 << "\x1b[1;37m: " << S << "\x1b[0m\n";
    }
    
    DTest::Diagnostic D;
    D <<
    DTest::TestData{"Util::String::Words", Test_String_Words} <<
    DTest::TestData{"Util::AppBook", Test_String_Words};
    
    
    D.Run(Args);
    Args.clear();
    return 0;
}

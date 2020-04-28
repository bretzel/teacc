//
// Created by bretzel on 20-04-25.
//

#include "Test.h"


using teacc::Util::String;
using teacc::Util::Rem;
using teacc::Util::Expect;



auto main(int argc, char** argv) -> int
{
    String::Collection Args = String::ArgsArray(argc, argv);
    
    DTest::Diagnostic D;
    D
    << DTest::TestData{"Util::String::Words", &UtilStringWords::Run}
    << DTest::TestData{"Util::AppBook", UtilAppBook::Run};
    
   
    D.Run(Args);
    Args.clear();
    return 0;
}

Expect<> UtilStringWords::Run(String::Collection Args_)
{
    std::cout << __PRETTY_FUNCTION__ << " \\O/!\n";
    return Expect<>();
}
Expect<> UtilAppBook::Run(String::Collection Args_)
{
    std::cout << __PRETTY_FUNCTION__ << " \\O/!\n";
    return Expect<>();
}

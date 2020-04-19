//
// Created by bretzel on 20-04-18.
//

//#include <teacc/Util/String.h>
#include "UtilTests.h"

using namespace teacc::Util;


auto main(int argc, char**argv) -> int
{
    
    UtilTests Test;
    Expect<> E = Test.Init(argc, argv);
    
    String Str = "Hello, World!\n ==> This is the VeryFirst of the %s Tests!\n----------------------------------------------------------\n";
    Str << " teacc::Util Library";
    std::cout << Str();
    
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
    String::Collection Args = String::ArgsArray(argc, argv);
    return {(
        Rem::Save() << Rem::Type::Debug << Rem::Type::Info << __PRETTY_FUNCTION__ << ": Start."
    )};
    
}

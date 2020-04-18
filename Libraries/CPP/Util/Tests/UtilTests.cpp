//
// Created by bretzel on 20-04-18.
//

#include <teacc/Util/String.h>


using teacc::Util::String;


auto main(int argc, char**argv) -> int
{
    String Str = "Hello, World!\n ==> This the VeryFirst of the %s Tests!\n----------------------------------------------------------\n";
    Str << "teacc::Util::Library";
    std::cout << Str();
    
    return 0;
}


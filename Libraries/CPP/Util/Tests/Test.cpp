//
// Created by bretzel on 20-04-25.
//

#include "Test.h"


auto main(int argc, char** argv) -> int
{
    using namespace teacc::Util;
    String::Collection Args = String::ArgsArray(argc, argv);
    teacc::String__TEST test = {"String::Words", Args);
    
}
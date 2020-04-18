//
// Created by bretzel on 20-04-18.
//

//#ifndef UTIL_UTILTESTS_H
//#define UTIL_UTILTESTS_H

#pragma once

#include <teacc/Util/Rem.h>

namespace teacc::Util
{

class UtilTests
{
public:
    
    UtilTests() = default;
    ~UtilTests();
    
    Expect <> Init(int argc, char** argv);
    
    
};

}
//#endif //UTIL_UTILTESTS_H

//
// Created by bretzel on 20-04-24.
//

//#ifndef UTIL_UTILTESTS_H
//#define UTIL_UTILTESTS_H

#pragma once
#include "include/teacc/Diagnostics/Diagnostic.h"
#include <teacc/Util/String.h>

namespace Diag
{



class UtilTests : public Test
{
    
    
    Expect<> TestStringWords();
    Expect<> TestAppBook();
    
public:
    UtilTests(std::string Name_);
    
    Expect<> Run() override;
};





}
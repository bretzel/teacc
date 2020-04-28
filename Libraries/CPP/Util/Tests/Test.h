//
// Created by bretzel on 20-04-25.
//

#pragma once

#include <teacc/Util/Rem.h>
#include <teacc/Diagnostics/Diagnostic.h>

namespace teacc::Util
{

struct UtilStringWords
{
public:
    static Expect<> Run(String::Collection Args_);
    
};


struct UtilAppBook
{
public:
    static Expect<> Run(String::Collection Args_);
};

}




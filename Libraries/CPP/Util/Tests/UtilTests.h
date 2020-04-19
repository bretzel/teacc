//
// Created by bretzel on 20-04-18.
//

//#ifndef UTIL_UTILTESTS_H
//#define UTIL_UTILTESTS_H

#pragma once

#include <teacc/Util/Rem.h>

namespace teacc::Util
{


/*!
 * @brief
 *
 * @todo Build a stacked Tests[Data] structure containing its own local diagnostics. :)
 */
 
class UtilTests
{
    struct DiagnosticData
    {
        using Collection = std::vector<DiagnosticData>;
        using Iterator   = Collection::iterator;
        
        std::string mName;
        Expect<> mResult = Rem::Int::Unset;
        
        std::string operator()();
    };
    
    DiagnosticData::Collection mDiagnostics;
    
    
public:
    
    UtilTests() = default;
    ~UtilTests();
    
    Expect <> Init(int argc, char** argv);
    Expect <> TestAppLog();
    
    Expect <> Run(int argc, char **argv);
    Expect <> TestString();
    
    
};

}
//#endif //UTIL_UTILTESTS_H

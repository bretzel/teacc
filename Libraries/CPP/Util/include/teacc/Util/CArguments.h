//
// Created by bretzel on 20-04-18.
//

//#ifndef UTIL_CARGUMENTS_H
//#define UTIL_CARGUMENTS_H

#pragma once

#include <teacc/Util/Rem.h>

namespace teacc::Util
{


class UTIL_LIB CArg
{
    String::Collection mArgValues;
    String::CIterator mCursor;
    
public:
    
    using Collection = std::vector<CArg>;
    using Iterator   = Collection::iterator;
    
    struct Params{
        bool Opt    = true; // = optional.
        int  nArgs  = -1;   // -1 = not specified; (0 or unlimited, such as '*' glob from the shell)
        std::string mLSwitch;
        std::string mShort;
        //... To be continued
    };
    
    CArg() = default;
    ~CArg() = default;
 
    CArg(const CArg& A);
    CArg(CArg &&A) noexcept;
    
    CArg& operator = (const CArg& A) ;
    CArg& operator = (CArg && A) noexcept;
    
    CArg& operator << (const std::string& A);
    
    
    [[nodiscard]] std::size_t NumArgs() const { return mArgValues.size(); }
    
    
};

class UTIL_LIB CArguments
{

};

}

//#endif //UTIL_CARGUMENTS_H

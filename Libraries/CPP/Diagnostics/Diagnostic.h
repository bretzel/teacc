//
// Created by bretzel on 20-04-21.
//

//#ifndef UTIL_DIAGNOSTIC_H
//#define UTIL_DIAGNOSTIC_H

#pragma once

#include <teacc/Util/Rem.h>



namespace teacc
{
class Diagnostic
{
    using Collection = std::vector<Diagnostic>;
    std::string mName;
public:
    // -- Let's see and learn:
    Diagnostic() = default;
    Diagnostic(const Diagnostic&) = default;
    Diagnostic(Diagnostic&&) = default;
    Diagnostic& operator=(Diagnostic&&) noexcept = default;
    Diagnostic& operator=(const Diagnostic&) = default;
    //------------------------
    
    Diagnostic(std::string Name_);
    ~Diagnostic();
    
    Util::Expect <> Run();
    
    
    


};
}


//#endif //UTIL_DIAGNOSTIC_H

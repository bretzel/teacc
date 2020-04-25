//
// Created by bretzel on 20-04-25.
//

#pragma once

#include <teacc/Diagnostics/Diagnostic.h>


namespace teacc
{

class String__TEST : public Diag::Test
{
    String::Word::Collection mWords;
    
public:
    
    Expect<> Run() override;
    
    
};


}




//
// Created by bretzel on 20-04-24.
//

#include "UtilTests.h"

namespace Diag
{
Expect<> Diag::UtilTests::Run()
{
    (void)TestStringWords();
    //...
    return TestAppBook();
}


Expect<> UtilTests::TestStringWords()
{
    return (
        Rem::Save() <<
        Rem::Type::Internal << ": " << " [Test]Util: 'String::Words' :" << Rem::Int::Implement
    );
}


teacc::Util::Expect<> Diag::UtilTests::TestAppBook()
{
    return (
        Rem::Save() <<
        Rem::Type::Internal << ": " << " [Test]Util: 'AppBook' :" << Rem::Int::Implement
    );
}
UtilTests::UtilTests(std::string Name_) : Test(Name_) {}

}
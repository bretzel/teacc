//
// Created by bretzel on 20-04-20.
//

#include "LexerTests.h"

Expect<> LexerTests::Run(String::Collection Args_)
{
    teacc::TokenData Token;
    const char* TestStr = "><=2;";
    Token = teacc::TokenData::Scan(TestStr);
    if(Token)
    {
        std::cout << "Token::Info [" << Token.Attr() << ":{" << Token.SemanticTypes() << "}]\n";
    }
    else
    {
        return (Rem::Save() << Rem::Type::Error << ": TokenData::Scan failed on '" << TestStr << "'");
    }
    
    std::cout << __PRETTY_FUNCTION__ << ":-> \\O/!\n";
    return Rem::Int::Implement;
}





using teacc::Util::String;
using teacc::Util::Rem;
using teacc::Util::Expect;



auto main(int argc, char** argv) -> int
{
    String::Collection Args = String::ArgsArray(argc, argv);
    
    DTest::Diagnostic D;
    D
    << DTest::TestData{"Lexer::TokenData::Scan", &LexerTests::Run};
    //<< DTest::TestData{"Util::AppBook", UtilAppBook::Run};
    
   
    D.Run(Args);
    Args.clear();
    return 0;
}

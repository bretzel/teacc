//
// Created by bretzel on 20-04-20.
//

#include "LexerTests.h"
#include <teacc/Lexer/Lexer.h>

Expect<> LexerTests::Run(String::Collection Args_)
{
    teacc::TokenData Token;
    const char* TestStr = "><=2;";
    Token = teacc::TokenData::Scan(TestStr);
    if(Token)
    {
        std::cout << "Token:[" << Token.Details() << "]\n";
    }
    else
    {
        return (Rem::Save() << Rem::Type::Error << ": ArgToken::Scan failed on '" << TestStr << "'");
    }
    
    std::cout << __PRETTY_FUNCTION__ << ":-> \\O/!\n";
    return Rem::Int::Implement;
}





using teacc::Util::String;
using teacc::Util::Rem;
using teacc::Util::Expect;

using teacc::TokenData;



auto main(int argc, char** argv) -> int
{
    String::Collection Args = String::ArgsArray(argc, argv);
    
    DTest::Diagnostic D;
    D << DTest::TestData{"Lexer::ArgToken::Scan", &LexerTests::Run};
    D.Run(Args);
    Args.clear();
    
    // --- Arbitrary [non-diagnostic] tests:
    std::string str = "Abcde_1 = 45.5 * 500 - sin 0.2*40;";
    TokenData::Collection Tokens;
    teacc::Lexer::Scanners Scanners;
    Scanners.Config() = {
        str.c_str(),
        &Tokens
    };
    
    std::cout << "Scanners::Scan(): \n";
    Expect<std::size_t> R = Scanners.Scan();
    std::cout << "Scanners return " << *R << "; produced " << Tokens.size()<< " Token(s)\n";
    
    for(auto  Token_ : Tokens)
        std::cout << Token_.Details(true ) << "\n";
    
    Rem::Clear([](Rem& R) {
       std::cout << R() << '\n';
    });
    
    
    return 0;
}

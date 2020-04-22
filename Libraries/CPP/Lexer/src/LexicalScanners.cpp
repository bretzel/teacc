//
// Created by bretzel on 20-04-22.
//

#include "teacc/Lexer/LexicalScanners.h"

namespace teacc::Lexer
{

bool LexicalScanners::InternalCursor::operator++()
{
    if(C>=E) return false;
    ++C;
    while((C < E) && (!isalnum(*C))) ++C;
    return true;
}

bool LexicalScanners::InternalCursor::operator++(int)
{
    return ++(*this);
}

bool LexicalScanners::InternalCursor::SkipWS()
{
    return ++(*this);
}


bool LexicalScanners::InternalCursor::Eof(const char *P)
{
    return C > E;
}

void LexicalScanners::InternalCursor::Sync()
{
    L = 1;
    const char* Pos_  = C;
    while(C>B)
    {
        if((*Pos_ == '\n') || (*Pos_ == '\r')) ++L;
        --C;
    }
    
    Pos_ = C;
    Col = 1;
    while((C>B) && (*C != '\n') && (*C != '\r'))
    {
        --C;
        ++Col;
    }
}


int LexicalScanners::InternalCursor::Index()
{
    return C-B;
}


std::string LexicalScanners::InternalCursor::ScanToEol()
{
    std::string Str;
    while( (C <= E ) && (*C != '\n') && (*C != '\r')) Str += *C++;
    return Str;
}


std::string LexicalScanners::InternalCursor::Line()
{
    std::string Str;
    
    const char* lb, *eb;
    lb = eb = C;
    while((lb>B) && (*lb!='\r') && (*lb != '\n')) --lb;
    if(lb>B) ++lb;
    while((eb<E) && (*eb != '\r') && (*eb != '\n')) ++eb;
    --eb;
    
    for(;lb<=eb; lb++) Str += *lb;
    return Str;
}

/*!
 * @brief Build a line String from the current position then Mark at the current columns.

  * @return std::string
  * @note : Must be Sync()'ed before calling Mark();
 
 */
std::string LexicalScanners::InternalCursor::Mark()
{
    Util::String Str = Line();
    Str << '\n';
    for(int x=0; x<Col; x++) Str << ' ';
    Str << '^';
    return Str();
}

std::string LexicalScanners::InternalCursor::Location()
{
    Util::String Str = "%d,%d";
    Str << L << Col;
    return Str();
}


Util::Rem::Int LexicalScanners::InternalCursor::ScanTo(const char *SubStr_)
{
    return Util::Rem::Int::Ok;
}
}

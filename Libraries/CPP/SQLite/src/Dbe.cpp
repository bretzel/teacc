//
// Created by bretzel on 20-04-21.
//

#include <teacc/DBE/Dbe.h>
#include <cstdlib>
#ifdef _WIN32
    ;
#else
#   include <unistd.h>
#   include <fcntl.h>
#endif
namespace teacc
{


using Util::Rem;

DBE::~DBE()
{

}

Util::Expect<> DBE::Open()
{
    // Need :
    if( mConfig.Name.empty())
        return ( Rem::Save() << Rem::Type::Error << " : A Database Name was not set. Configure this instance before Openning it" );
    if(DB)
        return ( Rem::Save() << Rem::Type::Error << " : A Database Handle is already in use for this instance of DBE. Close it before (Re-)Open a SQLite3 DB File" );
    //...
    Util::String Str = "DBE.%s.sqlite3";
    Str << mConfig.Name;
    Path = Str();
#ifdef _WIN32
    // ...
#else
    if(int Err; (Err = access(Str.c_str(), __S_IREAD|__S_IWRITE)))
    {
        Util::String ErrStr = " : Openning SQLite3 Database File: %s. ";
        ErrStr << strerror(errno);
        return (Rem::Save() << Rem::Type::Error << ErrStr());
    }
#endif
    
    return Rem::Int::Implement;
}


Util::Expect<> DBE::Close()
{
    return Rem::Int::Implement;
}
Util::Expect<> DBE::Create()
{
    // Need :
    if( mConfig.Name.empty())
        return ( Rem::Save() << Rem::Type::Error << " : A Database Name was not set. Configure this instance before Openning it" );
    if(DB)
        return ( Rem::Save() << Rem::Type::Error << " : A Database Handle is already in use for this instance of DBE. Close it before (Re-)Open a SQLite3 DB File" );
    //...
    Util::String Str = "DBE.%s.sqlite3";
    Str << mConfig.Name;
    Path = Str();
    
#ifdef _WIN32
    // ...
#else
    if(int Err; !(Err = access(Path.c_str(), __S_IREAD|__S_IWRITE)))
    {
        Util::String ErrStr = " : Creating SQLite3 Database File: %s. ";
        ErrStr << Path;
        return (Rem::Save() << Rem::Type::Error << ErrStr());
    }
#endif
    
    return Rem::Int::Implement;
}

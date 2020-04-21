//
// Created by bretzel on 20-04-21.
//

//#ifndef UTIL_DBE_H
//#define UTIL_DBE_H

#pragma once
#include <teacc/DBE/Lib.h>
#include <sqlite3.h>
#include <teacc/Util/Rem.h>
#include <map>


namespace  teacc
{

class DBE_LIB DBE
{
        std::string Path; ///< No, No DB in RAM.
        sqlite3 *   DB = nullptr;

public:
    struct ConfigData
    {
        std::string Name;
        //...
        
    };
private:
    
    ConfigData mConfig;
    
public:
    
    using Collection = std::map<std::string, DBE>; ///< Ok, Create Instances on site
    
    DBE() = default;
    virtual ~DBE();
    
    virtual Util::Expect<> Open();
    virtual Util::Expect<> Close();
    virtual Util::Expect<> Create();
    
    
};

}

//#endif //UTIL_DBE_H

//
// Created by bretzel on 20-04-18.
//

#include <teacc/Util/AppLog.h>


namespace teacc
{


AppLog* AppLog::mStaticInstance = nullptr;
AppLog::~AppLog()
{

}

AppLog &AppLog::Instance()
{
    return *AppLog::mStaticInstance;
}


AppLog &AppLog::Init(/* ... */)
{
    if(AppLog::mStaticInstance) return *AppLog::mStaticInstance;
    
    // ...init ...
    // test
    int C= AppLog::Aqua;
    return *AppLog::mStaticInstance;
}
AppLog::ConfigData &AppLog::Config()
{
    if(!AppLog::mStaticInstance)
        AppLog::mStaticInstance = new AppLog;
    
    return AppLog::mStaticInstance->mConfig;
    
}

//AppLog::Object::Object(AppLog::Object *_Parent):mParent(_Parent)
//{
//
//}

}

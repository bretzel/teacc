//
// Created by bretzel on 20-04-18.
//

#include <teacc/Util/AppBook.h>
#include <map>


namespace teacc
{


AppBook* AppBook::mStaticInstance = nullptr;
AppBook::~AppBook()
{
    delete mCurrentLog;
}

AppBook &AppBook::Instance()
{
    return *AppBook::mStaticInstance;
}


AppBook &AppBook::Init(/* ... */)
{
    if(AppBook::mStaticInstance) return *AppBook::mStaticInstance;
    ///@todo Do not polute static storage memory with more appropriate instance data.
    mStaticInstance->mComponentData = {
        {Reset   ,"\033[0m"},
        {Italic  ,""},
        {Sup     ,""},
        {Sub     ,""},
        {Code    ,""},
        {EndCode ,""},
        {Pre     ,""},
        {EndPre  ,""},
        {Eol     ,"\n"},
    };
    // Continue init...
    
    return *AppBook::mStaticInstance;
}
AppBook::ConfigData &AppBook::Config()
{
    if(!AppBook::mStaticInstance)
        AppBook::mStaticInstance = new AppBook;
    
    return AppBook::mStaticInstance->mConfig;
    
}

AppBook::Log &AppBook::Begin(AppBook::Prefix Prefix_)
{
    Log* L = new AppBook::Log(Prefix_);
    L->SetParent(AppBook::mStaticInstance->mCurrentLog);
    AppBook::mStaticInstance->mCurrentLog = L;
    //...
    return *L;
}

std::string AppBook::ToStr(AppBook::Prefix Prefix_)
{
    std::map<AppBook::Prefix, std::string> _ = {
        {AppBook:: Debug    ,"➤ Debug"},
        {AppBook:: Info     ,"⚫ Info"},
        {AppBook:: Error    ,"✘ Error"},
        {AppBook:: Warning  ,"⚑⚠ Warning"},
        {AppBook:: Exception,"⚡ Exception"},
        {AppBook:: Fatal    ,"☠ Fatal"},
        {AppBook:: Success  ,"✔ Success"},
        {AppBook:: Notice   ,"✎ Notice"}
    };
    return _[Prefix_];
}

AppBook &AppBook::End()
{
    AppBook::Instance().mText << AppBook::Instance().mCurrentLog->mText;
    delete AppBook::Instance().mCurrentLog;
    return AppBook::Instance();
}

AppBook::Log &AppBook::Log::operator<<(AppBook::Prefix Prefix_)
{
    mText << AppBook::ToStr(Prefix_);
    return *this;
}
AppBook::Log &AppBook::Log::operator<<(AppBook::Component C)
{
    mText << AppBook::Instance().mComponentData[C];
    return *this;
}


AppBook::Log::~Log()
{
    mText.Clear();
    delete mChild;
}

AppBook::Log::Log(AppBook::Prefix Prefix_):mPrefix(Prefix_){}



void AppBook::Log::SetParent(AppBook::Log *Parent_)
{
    mParent = Parent_;
    mParent->mChild = this;
}


void AppBook::Log::SetChild(AppBook::Log *Child_)
{
    if(!Child_) return;
    mChild = Child_;
    mChild->mIndent = mIndent + 4; // Hard coded indent.
}


void AppBook::Log::End()
{
    if(mParent)
        mParent->mText << mText;
    
    mText.Clear();
}
AppBook::Log &AppBook::Log::operator<<(AppBook::Color C)
{
    mText <<  "\x1b[38;5;%3dm" << static_cast<int>(C);
    return *this;
}

}

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
    std::cout << __PRETTY_FUNCTION__ << " ⚒ \\O/\n";
}

AppBook &AppBook::Instance()
{
    return *AppBook::mStaticInstance;
}


AppBook &AppBook::Init(/* ... */)
{
    if(!AppBook::mStaticInstance->mComponentData.empty()) return *AppBook::mStaticInstance;
    AppBook& Book = *AppBook::mStaticInstance;
    
    AppBook::mStaticInstance->mComponentData = {
        {TextCtl::Reset   ,"\033[0m"},
//        {TextCtl::Italic  ,""},
        {TextCtl::Sup     ,""},
        {TextCtl::Sub     ,""},
        {TextCtl::Code    ,""},
        {TextCtl::EndCode ,""},
//        {TextCtl::Pre     ,""},
//        {TextCtl::EndPre  ,""},
        {TextCtl::Eol     ,"\n"}
    };
    AppBook::mStaticInstance->mText
    << AppBook::mStaticInstance->mConfig.Title
    << AppBook::mStaticInstance->mComponentData[TextCtl::Eol];
    
    if(!Book.mConfig.Filename.empty())
    {
        // Not yet ready to output to the given file.
        Book.mFile = &std::cout; // It's that simple!!
    }
    else
        Book.mFile = &std::cout; // It's that simple!!
        
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
    if(AppBook::mStaticInstance->mCurrentLog)
        L->SetParent(AppBook::mStaticInstance->mCurrentLog);
    
    AppBook::mStaticInstance->mCurrentLog = L;
    (*L) << Prefix_ << ':';
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

void AppBook::End(std::function<void(const std::string &)> EndFN)
{
    AppBook::Instance().mText << AppBook::Instance().mCurrentLog->mText;
    if(EndFN)
        EndFN(AppBook::Instance().mText());
    
    delete AppBook::Instance().mCurrentLog;
    delete mStaticInstance;
}

std::string AppBook::Text()
{
    return AppBook::Instance().mText();
}

AppBook::Log &AppBook::Log::operator<<(AppBook::Prefix Prefix_)
{
    mText << AppBook::ToStr(Prefix_);
    return *this;
}

AppBook::Log &AppBook::Log::operator<<(teacc::TextCtl C)
{
    mText << AppBook::Instance().mComponentData[C];
    return *this;
}


AppBook::Log::~Log()
{
    std::cout << __PRETTY_FUNCTION__ << " ⚒ \\O/\n";
    mText.Clear();
    delete mChild;
}

AppBook::Log::Log(AppBook::Prefix Prefix_):mPrefix(Prefix_){}



void AppBook::Log::SetParent(AppBook::Log *Parent_)
{
    if(!Parent_) return;
    
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
    if(mChild)
        mText << mChild->mText;
}

AppBook::Log &AppBook::Log::operator<<(teacc::Color C)
{
    mText <<  "\x1b[38;5;%3dm" << static_cast<int>(C);
    return *this;
}
std::string AppBook::Log::Endl()
{
    return AppBook::mStaticInstance->mComponentData[TextCtl::Eol];
}

}

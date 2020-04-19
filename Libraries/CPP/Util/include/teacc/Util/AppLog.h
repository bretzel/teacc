//
// Created by bretzel on 20-04-18.
//

//#ifndef UTIL_APPLOG_H
//#define UTIL_APPLOG_H

#pragma once

#include <teacc/Util/Rem.h>

#include <map>
#include <fstream>
#include <ctime>
#include <utility>
#include <vector>
#include <stack>


namespace teacc
{
// No namespace here. AppLog to be used so fuKJK* too often.

using Util::String;

/*!
 * @brief Rewrite and rebase of my journal logger.
 *
 * @author &copy; 2020, Serge Lussier (lussier.serge@gmail.com)
 *
 *
 */
 
class UTIL_LIB AppLog
{
    
    String mText; ///< "Text Accumulator" of this AppLog instance.
    
public:
    
    
    struct UTIL_LIB Object
    {
        String mText; ///< "Text Accumulator" of this AppLog::Object.
        Object* mParnet = nullptr;
        
        Object(Object *_Parent);
        virtual ~Object() = default; // For now.
    };
    
    struct Header : public AppLog::Object
    {
    
    };

}
//#endif //UTIL_APPLOG_H

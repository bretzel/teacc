//
// Created by bretzel on 20-04-17.
//

//#ifndef UTIL_LIB_H
//#define UTIL_LIB_H

#pragma once

//#pragma warning(once: 4251)


#ifdef Teacc
# undef Teacc
#endif

#ifdef _WIN32
#   pragma warning(disable : 4996)
//class __declspec(dllimport) std::thread;
#   define _CRT_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS

#   ifdef UTIL_DLL_EXPORT
#       define UTIL_LIB __declspec(dllexport)
#       if __GNUC__ >= 4
#           define UTIL_LIB __attribute__ ((visibility ("default")))
#           define PRIVATE_LIB  __attribute__ ((visibility ("hidden")))
#       else
#           define UTIL_LIB
#           define PRIVATE_LIB
#       endif
#   else
#       define UTIL_LIB __declspec(dllimport)
#   endif
#   else
#       define UTIL_LIB    // Not ms-Windows/MSVC
#endif

// Mandatory. Globally used where it needs to.

//---------------------------------------------

#ifndef DECLOBJ_ID
#define DECLOBJ_ID \
    private:\
        static  const  std::string OBJ_CLASSID; \
    public:\
        virtual const std::string& OBJ_CLASSNAME() const noexcept; \
    private:

#define  CLASSNAME_IMPL(CLASS) \
         const std::string  CLASS::CLASSID = #CLASS;\
         const std::string&  CLASS::CLASSNAME() const noexcept{ return CLASS::CLASSID; }
#endif

#ifndef _WIN32
#   define _strdup  strdup

#   include <thread>
#   include <cstdint>

#else
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
//#endif //UTIL_LIB_H

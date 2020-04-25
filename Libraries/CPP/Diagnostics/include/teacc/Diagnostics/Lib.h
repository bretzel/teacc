//
// Created by bretzel on 20-04-17.
//

//#ifndef DIAGNOSTIC_LIB_H
//#define DIAGNOSTIC_LIB_H

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

#   ifdef DIAGNOSTIC_DLL_EXPORT
#       define DIAGNOSTIC_LIB __declspec(dllexport)
#       if __GNUC__ >= 4
#           define DIAGNOSTIC_LIB __attribute__ ((visibility ("default")))
#           define PRIVATE_LIB  __attribute__ ((visibility ("hidden")))
#       else
#           define DIAGNOSTIC_LIB
#           define PRIVATE_LIB
#       endif
#   else
#       define DIAGNOSTIC_LIB __declspec(dllimport)
#   endif
#   else
#       define DIAGNOSTIC_LIB    // Not ms-Windows/MSVC
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
//#endif //DIAGNOSTIC_LIB_H

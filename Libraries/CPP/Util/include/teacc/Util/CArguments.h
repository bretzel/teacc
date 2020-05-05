/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Serge Lussier <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


#include <teacc/Util/Rem.h>


namespace teacc::Util
{




template <typename T> struct Option
{
    T*    mInstance     = nullptr;
    using OptFnPtr      = Expect<>(T::*)(const std::string&);
    
    using Collection    = std::vector<Option<T>>;
    using Iterator      = typename Collection::iterator;
    
    OptFnPtr    mFnPtr  = nullptr;
    // ----------------
    std::string Name;
    char        C=0;
    //-----------------
    
    int  nArgs = 0; ///< -1 = unspecified. 0 = none; 1...+ = 1 .. n args;
    bool mIsNVariable = false;
    std::vector<std::string> mData;
    
    
    Option(T& Instance_, Option::OptFnPtr OptFn_, std::string Name_, char C_, int Count_ = -1, bool IsVar_=false)
    {
        mInstance = &Instance_;
        mFnPtr = OptFn_;
        Name = std::move(Name_);
        C = C_;
        nArgs = Count_;
        mIsNVariable = IsVar_;
    }
    
    
};


}
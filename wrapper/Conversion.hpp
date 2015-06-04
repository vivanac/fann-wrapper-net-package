/*
 *
 *  Fast Artificial Neural Network (fann) C# Wrapper
 *  Copyright (C) 2010 created by james (at) jamesbates.net
 *  
 *  On LinkedIn here http://uk.linkedin.com/in/alexanderjamesbates 
 *
 *  This wrapper is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This wrapper is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#pragma once

#include <vector>
#include "Connection.h"

using namespace System::Collections::Generic;

inline std::string toNative(System::String^ in)
{
	return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(in).ToPointer();
}

inline System::String^ toManaged(const std::string& in)
{
	return gcnew System::String(in.c_str());
}


template<typename T>
inline std::vector<T> toNative(System::Collections::Generic::IEnumerable<T^>^ inVal)
{
	std::vector<T> rval(inVal->Count);

	for each( T item in inVal)
	{
		rval.push_back(item);
	}

	return rval;
}


template<typename T>
inline array<array<T,1>^,1> ^toManaged(T** in, size_t sizeX , size_t sizeY)
{
	array<array<T,1>^,1> ^rval = gcnew array<array<T,1>^,1>(sizeX);

	for(size_t x=0;x<sizeX;++x)
	{
		rval[x] = toManaged(in[x],sizeY);
	}

	return rval;
}


template<typename T>
inline array<T, 1> ^toManaged(T* in, size_t sizeX)
{
	array<T, 1> ^rval = gcnew array<T, 1>(sizeX);

	for(size_t x=0;x<sizeX;++x)
	{
		rval[x] = in[x];
	}

	return rval;
}

inline array<FANN::Net::Connection^,1>^ toManaged(FANN::connection* connections, size_t sizeX)
{
	array<FANN::Net::Connection^,1>^ rval = gcnew array<FANN::Net::Connection^,1>(sizeX);

	for(size_t i=0;i<sizeX;++i)
	{
		rval[i] = gcnew FANN::Net::Connection(new FANN::connection(connections[i]));
	}

	return rval;
}

inline std::vector<FANN::connection> toNative(array<FANN::Net::Connection^,1>^ inVal)
{
	std::vector<FANN::connection> rval(inVal->Length);

	for each( FANN::Net::Connection^ conn in inVal)
	{
		rval.push_back(conn->Raw());
	}

	return rval;
}
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

#include <memory>

template<typename T>
public ref class ProxyImpl
{
internal:
	
	typedef T ProxiedType;

	ProxyImpl()
		: m_raw(new T),m_owner(true)
	{
	}

	ProxyImpl(T* raw)
		: m_raw(raw), m_owner(true)
	{
	}

	ProxyImpl(T* raw,bool owner)
		: m_raw(raw), m_owner(owner)
	{
	}

	~ProxyImpl()
	{
		if(m_owner)
			delete m_raw;
	}

	T& Raw() 
	{ 
		return *m_raw;
	}

private:
	bool m_owner;
	T* m_raw;

};
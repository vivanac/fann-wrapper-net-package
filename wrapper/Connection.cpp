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


#include "StdAfx.h"
#include "Connection.h"


namespace FANN
{
namespace Net
{


Connection::Connection(void)
: ProxyImpl<FANN::connection>(new FANN::connection)
{

}

Connection::Connection(FANN::connection *data)
: ProxyImpl<FANN::connection>(data)
{

}

Connection::Connection(FANN::connection *data,bool owner)
: ProxyImpl<FANN::connection>(data,owner)
{

}


Connection::~Connection(void)
{
}

unsigned int Connection::FromNeuron::get()
{
    return Raw().from_neuron;
}

void Connection::FromNeuron::set(unsigned int x)
{
    Raw().from_neuron = x;
}

unsigned int Connection::ToNeuron::get()
{
    return Raw().to_neuron;
}
        
void Connection::ToNeuron::set(unsigned int x)
{
    Raw().to_neuron = x;
}
    
fann_type Connection::Weight::get()
{
    return Raw().weight;
}

void Connection::Weight::set(fann_type x)
{
    Raw().weight = x;
}
    

}
}


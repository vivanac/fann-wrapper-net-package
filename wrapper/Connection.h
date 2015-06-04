#pragma once

#pragma managed (push,off)
#include "doublefann.h"
#include "fann_cpp.h"
#pragma managed (pop)

#include "ProxyImpl.h"

#using <mscorlib.dll>

using namespace System;

namespace FANN
{
namespace Net
{

public ref class Connection : ProxyImpl<FANN::connection>
{
public:
	Connection(void);
	virtual ~Connection(void);

	property unsigned int FromNeuron
    {
        unsigned int get();
        void set(unsigned int x);
    }

	property unsigned int ToNeuron
    {
        unsigned int get();
        void set(unsigned int x);
    }

	property fann_type Weight
    {
        fann_type get();
        void set(fann_type x);
    }
internal:
	Connection(FANN::connection *data,bool owner);
	Connection(FANN::connection *data);
};

}
}

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
#include "TrainingData.h"
 
#include <vcclr.h>
#include <vector>
#include "Conversion.hpp"

#include <boost/multi_array.hpp>
#include <boost/scoped_array.hpp>

namespace FANN
{
namespace Net
{

TrainingData::TrainingData(void)
: ProxyImpl<FANN::training_data>(new FANN::training_data)
{
	m_Instances[(unsigned int)&Raw()] = this;
}

TrainingData::TrainingData(FANN::training_data *data)
: ProxyImpl<FANN::training_data>(data)
{
	m_Instances[(unsigned int)&Raw()] = this;
}

TrainingData::TrainingData(FANN::training_data *data,bool owner)
: ProxyImpl<FANN::training_data>(data,owner)
{
	m_Instances[(unsigned int)&Raw()] = this;
}

TrainingData^ TrainingData::Instance(FANN::training_data* data)
{
	unsigned int idata = (unsigned int)data;

	if(!m_Instances->ContainsKey(idata))
	{
		m_Instances[idata] = gcnew TrainingData(data,false);
	}

	return m_Instances[idata];
}

TrainingData::~TrainingData(void)
{
	m_Instances->Remove((unsigned int)&Raw());
}

bool TrainingData::ReadTrainFromFile(System::String^ filename)
{
	return Raw().read_train_from_file(toNative(filename));
}

bool TrainingData::SaveTrain(System::String^ filename)
{
	return Raw().save_train(toNative(filename));
}

bool TrainingData::SaveTrainToFixed(System::String^ filename, unsigned int decimalPoint)
{
	return Raw().save_train_to_fixed(toNative(filename),decimalPoint);
}

void TrainingData::ShuffleTrainData()
{
	Raw().shuffle_train_data();
}

void TrainingData::Merge(TrainingData^ data)
{
	Raw().merge_train_data(data->Raw());
}

unsigned int TrainingData::TrainingDataLength::get()
{
	return Raw().length_train_data();
}

int TrainingData::NumInputTrainData::get()
{
	return Raw().num_input_train_data();
}

int TrainingData::NumOutputTrainData::get()
{
	return Raw().num_output_train_data();
}

array<array<fann_type,1>^,1> ^TrainingData::Input::get()
{
	return toManaged<fann_type>(Raw().get_input(),Raw().length_train_data(),Raw().num_input_train_data());
}

array<array<fann_type,1>^,1> ^TrainingData::Output::get()
{
	return toManaged(Raw().get_output(),Raw().length_train_data(),Raw().num_output_train_data());
}

template<typename T>
class ArrayDeleter 
{ 
public:     
	void operator () (T* d) const    
	{         
		delete [] d;     
	} 
}; 

void TrainingData::SetTrainData(unsigned int numData,
        unsigned int numInput,array<array<fann_type,1>^,1> ^input,
        unsigned int numOutput,array<array<fann_type,1>^,1> ^output)
{
	typedef boost::multi_array<double, 2> array_type;
	//typedef array_type::index input;
	array_type inputsMulti(boost::extents[numData][numInput]);
	array_type outputsMulti(boost::extents[numData][numOutput]);

	boost::scoped_array<fann_type*> fannInput(new fann_type*[numData]);
	boost::scoped_array<fann_type*> fannOutput(new fann_type*[numData]);

	for(size_t i=0;i<numData;++i)
	{
		fannInput[i] = &inputsMulti[i][0];
		for(size_t j=0;j<numInput;++j)
		{
			inputsMulti[i][j] = input[i][j];
		}

		fannOutput[i] = &outputsMulti[i][0];
		for(size_t j=0;j<numOutput;++j)
		{
			outputsMulti[i][j] = output[i][j];
		}
	}

	Raw().set_train_data(numData,numInput,&fannInput[0],numOutput,&fannOutput[0]);
	
}

class CallTranslator
{
public:
	CallTranslator(TrainingData::CallbackType^ fun)
	{
		current_callback = fun;
	}

	static void FANN_API translate_callback(
					unsigned int a,
					unsigned int b,
					unsigned int c,
					fann_type * d,
					fann_type * e)
	{
		current_callback->Invoke(a,b,c,toManaged(d,b),toManaged(e,c));
	}

private:
	
	static gcroot<TrainingData::CallbackType^> current_callback;
};

gcroot<TrainingData::CallbackType^> CallTranslator::current_callback;

typedef void (FANN_API *TrainingCallback)( unsigned int,unsigned int,unsigned int,fann_type * ,fann_type * );

void TrainingData::CreateTrainFromCallback(unsigned int numData,
                                      unsigned int numInput,
                                      unsigned int numOutput,
									  TrainingData::CallbackType^ fun)
{
	CallTranslator translator(fun);

	Raw().create_train_from_callback(numData,numInput,numOutput,CallTranslator::translate_callback);

}

void TrainingData::ScaleInputTrainData(fann_type newMin, fann_type newMax)
{
	Raw().scale_input_train_data(newMin,newMax);
}

void TrainingData::ScaleOutputTrainData(fann_type newMin, fann_type newMax)
{
	Raw().scale_output_train_data(newMin,newMax);
}

void TrainingData::ScaleTrainData(fann_type newMin, fann_type newMax)
{
	Raw().scale_train_data(newMin,newMax);
}

void TrainingData::SubsetTrainData(unsigned int pos, unsigned int length)
{
	Raw().subset_train_data(pos,length);
}


}
}

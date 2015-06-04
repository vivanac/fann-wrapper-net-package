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



#pragma managed (push,off)
#include "doublefann.h"
#include "fann_cpp.h"
#pragma managed (pop)

#include "ProxyImpl.h"

#using <mscorlib.dll>

using namespace System;
using namespace System::Collections::Generic;

namespace FANN
{
namespace Net
{

public ref class TrainingData : ProxyImpl<FANN::training_data>
{
public:
	delegate void	CallbackType (  unsigned int,
								 unsigned int,
								 unsigned int,
								 array<fann_type,1>^ ,
								 array<fann_type,1>^ );


	TrainingData(void);
	virtual ~TrainingData(void);


	bool ReadTrainFromFile(System::String^ filename);

    bool SaveTrain(System::String^ filename);

    bool SaveTrainToFixed(System::String^ filename, unsigned int decimalPoint);

    void ShuffleTrainData();

    void Merge(TrainingData^ data);

	property unsigned int TrainingDataLength
	{
		unsigned int get();
	}

	property int NumInputTrainData
	{
		int get();
	}

	property int NumOutputTrainData
	{
		int get();
	}

    property array<array<fann_type,1>^,1> ^ Input
	{
		array<array<fann_type,1>^,1> ^ get();
	}

    property array<array<fann_type,1>^,1> ^ Output
	{
		array<array<fann_type,1>^,1> ^ get();
	}


    void SetTrainData(unsigned int numdata,
        unsigned int numInput,array<array<fann_type,1>^,1> ^input,
        unsigned int numOutput,array<array<fann_type,1>^,1> ^output);
	



	void CreateTrainFromCallback(unsigned int numdata,
									  unsigned int numinput,
									  unsigned int numOutput,
									  CallbackType^ fun);

	void ScaleInputTrainData(fann_type newMin, fann_type newMax);

	void ScaleOutputTrainData(fann_type newMin, fann_type newMax);
	void ScaleTrainData(fann_type newMin, fann_type newMax);

	void SubsetTrainData(unsigned int pos, unsigned int length);
/*
	event CallbackType^ Callback
	{
		void add( CallbackType^ handler );
		void remove( CallbackType^ handler );
		void raise(unsigned int a, unsigned int b, unsigned int c, array<fann_type,1>^ d, array<fann_type,1>^ e);
	}
*/
internal:
	TrainingData(FANN::training_data *data,bool owner);
	TrainingData(FANN::training_data *data);
	static TrainingData^ Instance(FANN::training_data* data);
	CallbackType^ callbackHandler;

private:
	static Dictionary<unsigned int,TrainingData^>^ m_Instances = gcnew Dictionary<unsigned int,TrainingData^>();

};

}
}

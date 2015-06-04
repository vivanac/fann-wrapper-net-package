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
#include "Connection.h"
#include "TrainingData.h"
#using <mscorlib.dll>
#include <vcclr.h>


using namespace System;
using namespace System::Collections::Generic;

using namespace System::Runtime::InteropServices;

namespace FANN
{
namespace Net
{

public enum class ErrorFunction {
    Linear = FANN_ERRORFUNC_LINEAR,
    TanH
};

public enum class StopFunction
{
    MSE = FANN_STOPFUNC_MSE,
    Bit
};

public enum class TrainingAlgorithm {
    Incremental = FANN_TRAIN_INCREMENTAL,
    Batch,
    RProp,
    QuickProp
};

public enum class ActivationFunction {
	Linear = FANN_LINEAR,
    Threshold,
    ThresholdSymmetric,
    Sigmoid,
    SigmoidStepWise,
    SigmoidSymmetric,
    SigmoidSymmetricStepWise,
    Gaussian,
    GaussianSymmetric,
    GaussianStepwise,
    Elliot,
    ElliotSymmetric,
    LinearPiece,
    LinearPieceSymmetric,
    SinSymmetric,
    CosSymmetric
};

public enum class NetworkType
{
    Layer = FANN_NETTYPE_LAYER,
    ShortCut
};

public ref class NeuralNet : ProxyImpl<FANN::neural_net>
{
public:
    delegate int CallbackType (NeuralNet^ net, TrainingData^ train,
        unsigned int maxEpochs, unsigned int epochsBetweenReports,
		float desiredError, unsigned int epochs);


	NeuralNet(void);
	virtual ~NeuralNet(void);

    //bool Createstandard(unsigned int numLayers, ...);
	bool CreateStandardArray(array<unsigned int,1>^ layers);
    //bool Createsparse(float connection_rate, unsigned int numLayers, ...);
    bool CreateSparseArray(float connectionRate,array<unsigned int,1>^ layers);
    //bool Createshortcut(unsigned int numLayers, ...);
    bool CreateShortcutArray(array<unsigned int,1>^ layers);
    array<fann_type, 1> ^ Run(array<fann_type, 1> ^input);
    void RandomizeWeights(fann_type minWeight, fann_type maxWeight);
    void InitWeights(TrainingData^ data);
    void PrintConnections();
    bool CreateFromFile(System::String^ configurationFile);
    bool Save(System::String^ configurationFile);
    int SaveToFixed(System::String^ configurationFile);
    void Train(fann_type *input, fann_type *desiredOutput);
    float TrainEpoch(TrainingData^ data);
    void TrainOnData(TrainingData^ data, unsigned int maxEpochs,
        unsigned int epochs_between_reports, float desired_error);
    void TrainOnFile(System::String^ filename, unsigned int maxEpochs,
        unsigned int epochs_between_reports, float desired_error);
    fann_type * Test(fann_type *input, fann_type *desiredOutput);
    float TestData(TrainingData^ data);
    float GetMSE();
    void ResetMSE();
    //void Setcallback(callback_type callback, void *user_data);
    void PrintParameters();
    TrainingAlgorithm GetTrainingAlgorithm();
    void SetTrainingAlgorithm(TrainingAlgorithm trainingAlgorithm);
    float GetLearningRate();
    void SetLearningRate(float learningRate);
    ActivationFunction GetActivationFunction(int layer, int neuron);
    void SetActivationFunction(ActivationFunction activationFunction, int layer, int neuron);
    void SetActivationFunctionLayer(ActivationFunction activationFunction, int layer);
    void SetActivationFunctionHidden(ActivationFunction activationFunction);
    void SetActivationFunctionOutput(ActivationFunction activationFunction);
    fann_type GetActivationSteepness(int layer, int neuron);
    void SetActivationSteepness(fann_type steepness, int layer, int neuron);
    void SetActivationSteepnessLayer(fann_type steepness, int layer);
    void SetActivationSteepnessHidden(fann_type steepness);
    void SetActivationSteepnessOutput(fann_type steepness);
    ErrorFunction GetTrainErrorFunction();
    void SetTrainErrorFunction(ErrorFunction trainErrorFunction);
    float GetQuickPropDecay();
    void SetQuickPropDecay(float quickPropDecay);
    float GetQuickPropMu();
    void SetQuickPropMu(float quickPropMu);
    float GetRPropIncreaseFactor();
    void SetRPropIncreaseFactor(float rPropIncreaseFactor);
    float GetRPropDecreaseFactor();
    void SetRPropDecreaseFactor(float rPropDecreaseFactor);
    float GetRPropDeltaMin();
    void SetRPropDeltaMin(float rpropDeltaMin);
    float GetRPropDeltaMax();
    void SetRPropDeltaMax(float rpropDeltaMax);
    unsigned int GetNumInput();
    unsigned int GetNumOutput();
    unsigned int GetTotalNeurons();
    unsigned int GetTotalConnections();
#ifdef FIXEDFANN
    unsigned int Getdecimal_point();
    unsigned int Getmultiplier();
#endif
    NetworkType GetNetworkType();
    float GetConnectionRate();
    unsigned int GetNumLayers();
    void GetLayerArray(unsigned int *layers);
    void GetBiasArray(unsigned int *bias);
    void GetConnectionArray(array<Connection^,1>^ % connections);
    void SetWeightArray(array<FANN::Net::Connection^,1>^ connections);
    void SetWeight(unsigned int from_neuron, unsigned int toNeuron, fann_type weight);
    float GetLearningMomentum();
    void SetLearningMomentum(float learning_momentum);
    StopFunction GetTrainStopFunction();
    void SetTrainStopFunction(StopFunction trainStopFunction);
    fann_type GetBitFailLimit();
    void SetBitFailLimit(fann_type bitFailLimit);
    unsigned int GetBitFail();
    void CascadeTrainOnData(TrainingData^ data, unsigned int maxNeurons,
        unsigned int neuronsBetweenReports, float desiredError);
    void CascadeTrainOnFile(System::String^ filename, unsigned int maxNeurons,
        unsigned int neurons_between_reports, float desiredError);
    float GetCascadeOutputChangeFraction();
    void SetCascadeOutputChangeFraction(float cascadeOutputChangeFraction);
    unsigned int GetCascadeOutputStagnationEpochs();
    void SetCascadeOutputStagnationEpochs(unsigned int cascadeOutputStagnationEpochs);
    float GetCascadeCandidateChangeFraction();
    void SetCascadeCandidateChangeFraction(float cascadecandidateChangeFraction);
    unsigned int GetCascadeCandidateStagnationEpochs();
    void SetCascadeCandidateStagnationEpochs(unsigned int cascadecandidateStagnationEpochs);
    fann_type GetCascadeWeightMultiplier();
    void SetCascadeWeightMultiplier(fann_type cascadeWeightMultiplier);
    fann_type GetCascadeCandidateLimit();
    void SetCascadeCandidateLimit(fann_type cascadeCandidateLimit);
    unsigned int GetCascadeMaxOutEpochs();
    void SetCascadeMaxOutEpochs(unsigned int cascadeMaxOutEpochs);
    unsigned int GetCascadeMaxCandEpochs();
    void SetCascadeMaxCandEpochs(unsigned int cascadeMaxCandEpochs);
    unsigned int GetCascadeNumCandidates();
    unsigned int GetCascadeActivationFunctionsCount();
    ActivationFunction * GetCascadeActivationFunctions();
    void SetCascadeActivationFunctions(ActivationFunction *cascadeActivationFunctions,
        unsigned int cascadeActivationFunctionsCount);
    unsigned int GetCascadeActivationSteepnessesCount();
    fann_type *GetCascadeActivationSteepnesses();
    void SetCascadeActivationSteepnesses(fann_type *CascadeActivationSteepnesses,
        unsigned int CascadeActivationSteepnessesCount);
    unsigned int GetCascadeNumCandidateGroups();
    void SetCascadeNumCandidateGroups(unsigned int CascadeNumcandidate_groups);
    void ScaleTrain(TrainingData^ data);
    void DescaleTrain(TrainingData^ data);
    bool SetInputScalingParams(TrainingData^ data, float new_inputMin, float new_input_max);
    bool SetOutputScalingParams(TrainingData^ data, float newOutputMin, float newOutput_max);
    bool SetScalingParams(TrainingData^ data,
        float new_inputMin, float new_input_max, float newOutputMin, float newOutput_max);
    bool ClearScalingParams();
    void ScaleInput(array<fann_type, 1> ^ inputVector);
    void ScaleOutput(array<fann_type, 1> ^ output_vector);
    void DescaleInput(array<fann_type, 1> ^ input_vector);
    void DescaleOutput(array<fann_type, 1> ^ output_vector);
    void SetErrorLog(FILE *log_file);
    unsigned int GetErrNo();
    void ResetErrNo();
    void ResetErrStr();
	System::String^ GetErrStr();
    void PrintError();

public:
	event CallbackType^ Callback
	{
		void add( CallbackType^ handler );
		void remove( CallbackType^ handler );
		int raise(NeuralNet^ net, TrainingData^ train,
						unsigned int maxEpochs, unsigned int epochsBetweenReports,
						float desiredError, unsigned int epochs);
	}

internal:
	NeuralNet(FANN::neural_net* net);
	static NeuralNet^ Instance(FANN::neural_net* net);
	CallbackType^ callbackHandler;
	GCHandle gch;

	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	delegate int InternalCallbackType (neural_net &net, training_data &train,
		unsigned int max_epochs, unsigned int epochs_between_reports,
		float desired_error, unsigned int epochs, void *user_data);

	int InternalCallback(neural_net &net, training_data &train,
        unsigned int max_epochs, unsigned int epochs_between_reports,
        float desired_error, unsigned int epochs, void *user_data);

private:

	static Dictionary<unsigned int,NeuralNet^>^ m_Instances = gcnew Dictionary<unsigned int,NeuralNet^>();
	InternalCallbackType^ m_internalCallback;
};


}
}

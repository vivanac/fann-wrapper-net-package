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

#include <vector>

#include "NeuralNet.h"

#include "Conversion.hpp"



namespace FANN
{
namespace Net
{

class CallTranslator
{
public:
	CallTranslator(NeuralNet::CallbackType^ fun)
	{
		currentCallback = fun;
	}

	static int FANN_API translate_callback(neural_net &net, training_data &train,
        unsigned int max_epochs, unsigned int epochs_between_reports,
        float desired_error, unsigned int epochs, void *user_data)
	{
		currentCallback->Invoke(NeuralNet::Instance(&net),TrainingData::Instance(&train),max_epochs,epochs_between_reports,desired_error,epochs);
	}

private:
	
	static gcroot<NeuralNet::CallbackType^> currentCallback;
};

NeuralNet::NeuralNet(void)
: ProxyImpl<FANN::neural_net>(new FANN::neural_net)
{
	m_Instances[(unsigned int)&Raw()] = this;
}

NeuralNet::NeuralNet(FANN::neural_net* net)
: ProxyImpl<FANN::neural_net>(net)
{
	m_Instances[(unsigned int)&Raw()] = this;
}

NeuralNet::~NeuralNet(void)
{
	m_Instances->Remove((unsigned int)&Raw());
}

NeuralNet^ NeuralNet::Instance(FANN::neural_net* net)
{
	return m_Instances[(unsigned int)net];
}

bool NeuralNet::CreateStandardArray(array<unsigned int,1>^ layers)
{
	pin_ptr<unsigned int> pinned = &layers[0];

	return Raw().create_standard_array(layers->Length,pinned);
}


bool NeuralNet::CreateSparseArray(float connectionRate,array<unsigned int,1>^ layers)
{
	pin_ptr<unsigned int> pinned = &layers[0];
	return Raw().create_sparse_array(connectionRate,layers->Length,pinned);
}


bool NeuralNet::CreateShortcutArray(array<unsigned int,1>^ layers)
{
	pin_ptr<unsigned int> pinned = &layers[0];
	return Raw().create_shortcut_array(layers->Length,pinned);
}

array<fann_type, 1> ^NeuralNet::Run(array<fann_type, 1> ^input)
{
	pin_ptr<fann_type> pinnedPtr = &input[0];
	return toManaged(Raw().run(pinnedPtr),Raw().get_num_output());
}

void NeuralNet::RandomizeWeights(fann_type minWeight, fann_type maxWeight)
{
	Raw().randomize_weights(minWeight,maxWeight);
}

void NeuralNet::InitWeights(TrainingData^ data)
{
	Raw().init_weights(data->Raw());
}

void NeuralNet::PrintConnections()
{
	Raw().print_connections();
}

bool NeuralNet::CreateFromFile(System::String^ configuration_file)
{
	return Raw().create_from_file(toNative(configuration_file));
}

bool NeuralNet::Save(System::String^ configuration_file)
{
	return Raw().save(toNative(configuration_file));
}

int NeuralNet::SaveToFixed(System::String^ configuration_file)
{
	return Raw().save_to_fixed(toNative(configuration_file));
}

void NeuralNet::Train(fann_type *input, fann_type *desiredOutput)
{
	Raw().train(input,desiredOutput);
}

float NeuralNet::TrainEpoch(TrainingData^ data)
{
	return Raw().train_epoch(data->Raw());
}

void NeuralNet::TrainOnData(TrainingData^ data, unsigned int maxEpochs,
    unsigned int epochsBetweenReports, float desiredError)
{
	Raw().train_on_data(data->Raw(),maxEpochs,epochsBetweenReports,desiredError);
}

void NeuralNet::TrainOnFile(System::String^ filename, unsigned int maxEpochs,
    unsigned int epochsBetweenReports, float desiredError)
{
	Raw().train_on_file(toNative(filename),maxEpochs,epochsBetweenReports,desiredError);
}

fann_type * NeuralNet::Test(fann_type *input, fann_type *desiredOutput)
{
	return Raw().test(input,desiredOutput);
}

float NeuralNet::TestData(TrainingData^ data)
{
	return Raw().test_data(data->Raw());
}

float NeuralNet::GetMSE()
{
	return Raw().get_MSE();
}

void NeuralNet::ResetMSE()
{
	Raw().reset_MSE();
}

void NeuralNet::PrintParameters()
{
	Raw().print_parameters();
}

TrainingAlgorithm NeuralNet::GetTrainingAlgorithm()
{
	return (TrainingAlgorithm)Raw().get_training_algorithm();
}

void NeuralNet::SetTrainingAlgorithm(TrainingAlgorithm trainingAlgorithm)
{
	Raw().set_training_algorithm((FANN::training_algorithm_enum)trainingAlgorithm);
}

float NeuralNet::GetLearningRate()
{
	return Raw().get_learning_rate();
}

void NeuralNet::SetLearningRate(float LearningRate)
{
	Raw().set_learning_rate(LearningRate);
}

ActivationFunction NeuralNet::GetActivationFunction(int layer, int neuron)
{
	return (ActivationFunction)Raw().get_activation_function(layer,neuron);
}

void NeuralNet::SetActivationFunction(ActivationFunction activationFunction, int layer, int neuron)
{
	Raw().set_activation_function((FANN::activation_function_enum)activationFunction,layer,neuron);
}

void NeuralNet::SetActivationFunctionLayer(ActivationFunction activationFunction, int layer)
{
	Raw().set_activation_function_layer((FANN::activation_function_enum)activationFunction,layer);
}

void NeuralNet::SetActivationFunctionHidden(ActivationFunction activationFunction)
{
	Raw().set_activation_function_hidden((FANN::activation_function_enum)activationFunction);
}

void NeuralNet::SetActivationFunctionOutput(ActivationFunction activationFunction)
{
	Raw().set_activation_function_output((FANN::activation_function_enum)activationFunction);
}

fann_type NeuralNet::GetActivationSteepness(int layer, int neuron)
{
	return Raw().get_activation_steepness(layer,neuron);
}

void NeuralNet::SetActivationSteepness(fann_type steepness, int layer, int neuron)
{
	Raw().set_activation_steepness(steepness,layer,neuron);
}

void NeuralNet::SetActivationSteepnessLayer(fann_type steepness, int layer)
{
	Raw().set_activation_steepness_layer(steepness,layer);
}

void NeuralNet::SetActivationSteepnessHidden(fann_type steepness)
{
	Raw().set_activation_steepness_hidden(steepness);
}

void NeuralNet::SetActivationSteepnessOutput(fann_type steepness)
{
	Raw().set_activation_steepness_output(steepness);
}

ErrorFunction NeuralNet::GetTrainErrorFunction()
{
	return (ErrorFunction)Raw().get_train_error_function();
}

void NeuralNet::SetTrainErrorFunction(ErrorFunction trainErrorFunction)
{
	Raw().set_train_error_function((FANN::error_function_enum)trainErrorFunction);
}

float NeuralNet::GetQuickPropDecay()
{
	return Raw().get_quickprop_decay();
}

void NeuralNet::SetQuickPropDecay(float quickPropDecay)
{
	Raw().set_quickprop_decay(quickPropDecay);
}

float NeuralNet::GetQuickPropMu()
{
	return Raw().get_quickprop_mu();
}

void NeuralNet::SetQuickPropMu(float quickPropMu)
{
	Raw().set_quickprop_mu(quickPropMu);
}

float NeuralNet::GetRPropIncreaseFactor()
{
	return Raw().get_rprop_increase_factor();
}

void NeuralNet::SetRPropIncreaseFactor(float rpropIncreaseFactor)
{
	Raw().set_rprop_increase_factor(rpropIncreaseFactor);
}

float NeuralNet::GetRPropDecreaseFactor()
{
	return Raw().get_rprop_decrease_factor();
}

void NeuralNet::SetRPropDecreaseFactor(float rpropDecreaseFactor)
{
	Raw().set_rprop_decrease_factor(rpropDecreaseFactor);
}

float NeuralNet::GetRPropDeltaMin()
{
	return Raw().get_rprop_delta_min();
}

void NeuralNet::SetRPropDeltaMin(float rpropDeltaMin)
{
	Raw().set_rprop_delta_min(rpropDeltaMin);
}

float NeuralNet::GetRPropDeltaMax()
{
	return Raw().get_rprop_delta_max();
}

void NeuralNet::SetRPropDeltaMax(float rpropDeltaMax)
{
	Raw().set_rprop_delta_max(rpropDeltaMax);
}

unsigned int NeuralNet::GetNumInput()
{
	return Raw().get_num_input();
}

unsigned int NeuralNet::GetNumOutput()
{
	return Raw().get_num_output();
}

unsigned int NeuralNet::GetTotalNeurons()
{
	return Raw().get_total_neurons();
}

unsigned int NeuralNet::GetTotalConnections()
{
	return Raw().get_total_connections();
}

#ifdef FIXEDFANN
unsigned int NeuralNet::Getdecimal_point()
{
	return Raw().Getdecimal_point();
}

unsigned int NeuralNet::Getmultiplier()
{
	return Raw().Getmultiplier();
}
#endif

NetworkType NeuralNet::GetNetworkType()
{
	return (NetworkType)Raw().get_network_type();
}

float NeuralNet::GetConnectionRate()
{
	return Raw().get_connection_rate();
}

unsigned int NeuralNet::GetNumLayers()
{
	return Raw().get_num_layers();
}

void NeuralNet::GetLayerArray(unsigned int *layers)
{
	Raw().get_layer_array(layers);
}

void NeuralNet::GetBiasArray(unsigned int *bias)
{
	Raw().get_bias_array(bias);
}

void NeuralNet::GetConnectionArray(array<Connection^,1>^ % connections)
{
	std::vector<FANN::connection> connsVector(Raw().get_total_connections());

	Raw().get_connection_array(&connsVector[0]);
	connections = toManaged(&connsVector[0],connsVector.size());
}

void NeuralNet::SetWeightArray(array<Connection^,1>^ connections)
{
	Raw().set_weight_array(&(toNative(connections))[0],connections->Length);
}

void NeuralNet::SetWeight(unsigned int from_neuron, unsigned int to_neuron, fann_type weight)
{
	Raw().set_weight(from_neuron,to_neuron,weight);
}

float NeuralNet::GetLearningMomentum()
{
	return Raw().get_learning_momentum();
}

void NeuralNet::SetLearningMomentum(float learning_momentum)
{
	Raw().set_learning_momentum(learning_momentum);
}

StopFunction NeuralNet::GetTrainStopFunction()
{
	return (StopFunction)Raw().get_train_stop_function();
}

void NeuralNet::SetTrainStopFunction(StopFunction trainStopFunction)
{
	Raw().set_train_stop_function((FANN::stop_function_enum)trainStopFunction);
}

fann_type NeuralNet::GetBitFailLimit()
{
	return Raw().get_bit_fail_limit();
}

void NeuralNet::SetBitFailLimit(fann_type bitFailLimit)
{
	Raw().set_bit_fail_limit(bitFailLimit);
}

unsigned int NeuralNet::GetBitFail()
{
	return Raw().get_bit_fail();
}

void NeuralNet::CascadeTrainOnData(TrainingData^ data, unsigned int maxNeurons,
    unsigned int neuronsBetweenReports, float desiredError)
{
	Raw().cascadetrain_on_data(data->Raw(),maxNeurons,neuronsBetweenReports,desiredError);
}

void NeuralNet::CascadeTrainOnFile(System::String^ filename, unsigned int maxNeurons,
    unsigned int neuronsBetweenReports, float desiredError)
{
	Raw().cascadetrain_on_file(toNative(filename),maxNeurons,neuronsBetweenReports,desiredError);
}

float NeuralNet::GetCascadeOutputChangeFraction()
{
	return Raw().get_cascade_output_change_fraction();
}

void NeuralNet::SetCascadeOutputChangeFraction(float cascadeOutputChangeFraction)
{
	Raw().set_cascade_output_change_fraction(cascadeOutputChangeFraction);
}

unsigned int NeuralNet::GetCascadeOutputStagnationEpochs()
{
	return Raw().get_cascade_output_stagnation_epochs();
}

void NeuralNet::SetCascadeOutputStagnationEpochs(unsigned int cascadeOutputStagnationEpochs)
{
	Raw().set_cascade_output_stagnation_epochs(cascadeOutputStagnationEpochs);
}

float NeuralNet::GetCascadeCandidateChangeFraction()
{
	return Raw().get_cascade_candidate_change_fraction();
}

void NeuralNet::SetCascadeCandidateChangeFraction(float cascadeCandidateChangeFraction)
{
	Raw().set_cascade_candidate_change_fraction(cascadeCandidateChangeFraction);
}

unsigned int NeuralNet::GetCascadeCandidateStagnationEpochs()
{
	return Raw().get_cascade_candidate_stagnation_epochs();
}

void NeuralNet::SetCascadeCandidateStagnationEpochs(unsigned int cascadeCandidateStagnationEpochs)
{
	Raw().set_cascade_candidate_stagnation_epochs(cascadeCandidateStagnationEpochs);
}

fann_type NeuralNet::GetCascadeWeightMultiplier()
{
	return Raw().get_cascade_weight_multiplier();
}

void NeuralNet::SetCascadeWeightMultiplier(fann_type cascadeWeightMultiplier)
{
	Raw().set_cascade_weight_multiplier(cascadeWeightMultiplier);
}

fann_type NeuralNet::GetCascadeCandidateLimit()
{
	return Raw().get_cascade_candidate_limit();
}

void NeuralNet::SetCascadeCandidateLimit(fann_type cascadeCandidateLimit)
{
	Raw().set_cascade_candidate_limit(cascadeCandidateLimit);
}

unsigned int NeuralNet::GetCascadeMaxOutEpochs()
{
	return Raw().get_cascade_max_out_epochs();
}

void NeuralNet::SetCascadeMaxOutEpochs(unsigned int cascadeMaxOutEpochs)
{
	Raw().set_cascade_max_out_epochs(cascadeMaxOutEpochs);
}

unsigned int NeuralNet::GetCascadeMaxCandEpochs()
{
	return Raw().get_cascade_max_cand_epochs();
}

void NeuralNet::SetCascadeMaxCandEpochs(unsigned int cascadeMaxCandEpochs)
{
	Raw().set_cascade_max_cand_epochs(cascadeMaxCandEpochs);
}

unsigned int NeuralNet::GetCascadeNumCandidates()
{
	return Raw().get_cascade_num_candidates();
}

unsigned int NeuralNet::GetCascadeActivationFunctionsCount()
{
	return Raw().get_cascade_activation_functions_count();
}

ActivationFunction * NeuralNet::GetCascadeActivationFunctions()
{
	return (ActivationFunction*)Raw().get_cascade_activation_functions();
}

void NeuralNet::SetCascadeActivationFunctions(ActivationFunction *cascadeActivationFunctions,
    unsigned int cascadeActivationFunctionsCount)
{
	Raw().set_cascade_activation_functions((FANN::activation_function_enum*)cascadeActivationFunctions,cascadeActivationFunctionsCount);
}

unsigned int NeuralNet::GetCascadeActivationSteepnessesCount()
{
	return Raw().get_cascade_activation_steepnesses_count();
}

fann_type *NeuralNet::GetCascadeActivationSteepnesses()
{
	return Raw().get_cascade_activation_steepnesses();
}

void NeuralNet::SetCascadeActivationSteepnesses(fann_type *cascadeActivationSteepnesses,
    unsigned int cascadeActivationSteepnessesCount)
{
	Raw().set_cascade_activation_steepnesses(cascadeActivationSteepnesses,cascadeActivationSteepnessesCount);
}

unsigned int NeuralNet::GetCascadeNumCandidateGroups()
{
	return Raw().get_cascade_num_candidate_groups();
}

void NeuralNet::SetCascadeNumCandidateGroups(unsigned int cascadeNumCandidateGroups)
{
	Raw().set_cascade_num_candidate_groups(cascadeNumCandidateGroups);
}

void NeuralNet::ScaleTrain(TrainingData^ data)
{
	Raw().scale_train(data->Raw());
}

void NeuralNet::DescaleTrain(TrainingData^ data)
{
	Raw().descale_train(data->Raw());
}

bool NeuralNet::SetInputScalingParams(TrainingData^ data, float newInputMin, float newInputMax)
{
	return Raw().set_input_scaling_params(data->Raw(),newInputMin,newInputMax);
}

bool NeuralNet::SetOutputScalingParams(TrainingData^ data, float newOutputMin, float newOutputMax)
{
	return Raw().set_output_scaling_params(data->Raw(),newOutputMin,newOutputMax);
}

bool NeuralNet::SetScalingParams(TrainingData^ data,
    float newInputMin, float newInputMax, float newOutputMin, float newOutputMax)
{
	return Raw().set_scaling_params(data->Raw(),newInputMin,newInputMax,newOutputMin,newOutputMax);
}

bool NeuralNet::ClearScalingParams()
{
	return Raw().clear_scaling_params();
}

void NeuralNet::ScaleInput(array<fann_type, 1> ^inputVector)
{
	pin_ptr<fann_type> pinnedPtr = &inputVector[0]; 

	Raw().scale_input(pinnedPtr);
}

void NeuralNet::ScaleOutput(array<fann_type, 1> ^outputVector)
{
	pin_ptr<fann_type> pinnedPtr = &outputVector[0]; 
	Raw().scale_output(pinnedPtr);
}

void NeuralNet::DescaleInput(array<fann_type, 1> ^inputVector)
{
	pin_ptr<fann_type> pinnedPtr = &inputVector[0]; 
	Raw().descale_input(pinnedPtr);
}

void NeuralNet::DescaleOutput(array<fann_type, 1> ^outputVector)
{
	pin_ptr<fann_type> pinnedPtr = &outputVector[0]; 
	Raw().descale_output(pinnedPtr);
}

void NeuralNet::SetErrorLog(FILE *logFile)
{
	Raw().set_error_log(logFile);
}

unsigned int NeuralNet::GetErrNo()
{
	return Raw().get_errno();
}

void NeuralNet::ResetErrNo()
{
	Raw().reset_errno();
}

void NeuralNet::ResetErrStr()
{
	Raw().reset_errstr();	
}

System::String^ NeuralNet::GetErrStr()
{
	return toManaged(Raw().get_errstr());
}

void NeuralNet::PrintError()
{
	Raw().print_error();
}

int NeuralNet::InternalCallback(neural_net &net, training_data &train,
        unsigned int max_epochs, unsigned int epochs_between_reports,
        float desired_error, unsigned int epochs, void *user_data)
{
	int rval=0;

	{
		TrainingData managedTrain(&train,false);
		rval = Callback(this,%managedTrain,max_epochs,epochs_between_reports,desired_error,epochs);
	}

	return rval;
}

void NeuralNet::Callback::add( CallbackType^ handler )
{
	m_internalCallback = gcnew InternalCallbackType(this,&NeuralNet::InternalCallback);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(m_internalCallback);

	Raw().set_callback(static_cast<FANN::callback_type>(ptr.ToPointer()),0);
	callbackHandler += handler;
}

void NeuralNet::Callback::remove( CallbackType^ handler )
{
	callbackHandler -=handler;
}

int NeuralNet::Callback::raise(NeuralNet^ net, TrainingData^ train,
				unsigned int maxEpochs, unsigned int epochsBetweenReports,
				float desiredError, unsigned int epochs)
{
	return callbackHandler(net,train,maxEpochs,epochsBetweenReports,desiredError,epochs);
}


}
}

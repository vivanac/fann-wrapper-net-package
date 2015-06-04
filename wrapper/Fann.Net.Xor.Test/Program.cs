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


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using FANN.Net;

namespace Fann.Net.Xor.Test
{



    class Program
    {

        // Test function that demonstrates usage of the fann C++ wrapper
        private static void xor_test()
        {
            System.Console.WriteLine("XOR test started.");

            const float LearningRate = 0.7f;
            const uint numInput = 2;
            const uint numHidden = 3;
            const uint numOutput = 1;
            const float desired_error = 0;
            const uint max_iterations = 1000;
            const uint iterations_between_reports = 10;

            System.Console.WriteLine("Creating network.");

            NeuralNet net = new NeuralNet();
            
            List<uint> layers = new List<uint>();
            layers.Add(numInput);
            layers.Add(numHidden);
            layers.Add(numOutput);

            net.CreateStandardArray(layers.ToArray());

            net.SetLearningRate(LearningRate);

            net.SetActivationSteepnessHidden(1.0);
            net.SetActivationSteepnessOutput(1.0);

            net.SetActivationFunctionHidden(ActivationFunction.SigmoidSymmetric);
            net.SetActivationFunctionOutput(ActivationFunction.SigmoidSymmetric);

            net.SetTrainStopFunction(StopFunction.Bit);
            net.SetBitFailLimit(0.01f);
            // Set additional properties such as the training algorithm
            //net.SetTrainingAlgorithm(FANN::TRAIN_QuickProp);

            // Output network type and parameters
            System.Console.WriteLine("Network Type                         :  ");
            switch (net.GetNetworkType())
            {
                case NetworkType.Layer:
                    System.Console.WriteLine("LAYER");
                    break;
                case NetworkType.ShortCut:
                    System.Console.WriteLine("SHORTCUT");
                    break;
                default:
                    System.Console.WriteLine("UNKNOWN");
                    break;
            }
            net.PrintParameters();

            System.Console.WriteLine("Training network.");

            TrainingData data = new TrainingData();
            bool d = data.ReadTrainFromFile("xor.data");
            if (d)
            {
                // Initialize and train the network with the data
                net.InitWeights(data);

                System.Console.WriteLine("Max Epochs " + max_iterations + ". "
                    + "Desired Error: " + desired_error);

                net.Callback += (nn, train, max_epochs, epochs_between_reports, de, epochs)
                    =>
                    {
                        System.Console.WriteLine("Epochs     " + epochs + ". " + "Current Error: " + nn.GetMSE() + "\n");
                        return 0;
                    };

                net.TrainOnData(data, max_iterations,
                    iterations_between_reports, desired_error);

                System.Console.WriteLine("Testing network.");

                for (uint i = 0; i < data.TrainingDataLength; ++i)
                {
                    // Run the network on the test data
                    double calcOut = net.Run(data.Input[i])[0];

                    System.Console.WriteLine("XOR test (" + data.Input[i][0] + ", "
                         + data.Input[i][1] + ") -> " + calcOut
                         + ", should be " + data.Output[i][0] + ", "
                         + "difference = "
                         + Math.Abs(calcOut - data.Output[i][0]));
                }

                System.Console.WriteLine("Saving network.");

                // Save the network in floating point and fixed point
                net.Save("xor_float.net");
                uint decimal_point = (uint)net.SaveToFixed("xor_fixed.net");
                data.SaveTrainToFixed("xor_fixed.data", decimal_point);

                System.Console.WriteLine("XOR test completed.");

            }
            else
                Console.WriteLine("Training file not found");
        }
        
        static void Main(string[] args)
        {
            xor_test();
            Console.ReadLine();
        }
    }
}

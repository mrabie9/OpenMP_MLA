/** @file main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */



/* USER CODE BEGIN (1) */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include "../../data.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
int classify (double *results, int size_results){

    int final_class = 0;
    double final_score = *results;
    int i;

    for(i = 1 ; i < size_results ; i++){

        if(results[i] > final_score){
            final_class = i;
            final_score = results[i];

        }

    }

    return final_class;


}

/*

*/


typedef struct{

    double weights[4];
    double bias;
    int n_weights;
    

}neuron_l1_t;

typedef struct{

    double weights[8];
    double bias;
    int n_weights;
    

}neuron_l2_t;

typedef struct {

    neuron_l1_t l1_neurons[8];
    int length;

}layer1_t;

typedef struct {

    neuron_l2_t l2_neurons[8];
    int length;

}layer2_t;



typedef struct {
    layer1_t layer1;
    layer2_t layer2;
}neural_net_t;


double * run_neural_net(neural_net_t neural_net, double *test_data);
double _activation_func(double val);

/* USER CODE END */

int main(void)
{
    // Neurons
    neuron_l1_t l1_neurons[8] = {
       {.weights = { 0.18284023, -0.8529724 ,  0.9295352 ,  0.27745247}, .bias = -0.5623624, .n_weights=4},
       {.weights = {-0.17880775, -0.42715448,  0.5908963 ,  0.45988828}, .bias = -0.05714933, .n_weights=4},
       {.weights = {-0.48771185, -0.3112061 , -0.3137951 ,  0.5289104 }, .bias = -0.053803623, .n_weights=4},
       {.weights = { 0.24778503,  0.9340235 , -1.4063437 , -1.3005494 }, .bias =  0.27202815, .n_weights=4},
       {.weights = { 0.72132677, -0.12656425, -1.1483048 , -0.083784  }, .bias = 0.41053805, .n_weights=4},
       {.weights = { 0.05532144,  0.47561175, -0.17761162, -1.3145427 }, .bias = 0.28362706, .n_weights=4},
       {.weights = { 0.12644108, -0.6311569 ,  0.03945397, -0.53849036}, .bias = 0.025350625, .n_weights=4},
       {.weights = { 0.21844819,  0.30629316, -0.961491  , -0.46816182}, .bias = 0.6091357, .n_weights=4}
    };

    neuron_l2_t l2_neurons[3] = {
       {.weights = {-1.2635437 , -1.316526  ,  0.28543112,  1.3884338 ,  0.45282924,
                    1.0371606 ,  0.12748991,  0.6325952 }, .bias = -0.43309692, .n_weights=8},
       {.weights = { 0.497385  , -0.632777  ,  0.38966534, -1.2256211 , -0.19634834,
                    0.25377455,  0.6375568 , -0.5464157 } , .bias = -0.14760242, .n_weights=8},
       {.weights = { 0.3835234 ,  0.10146759, -0.32170305, -1.1918751 , -1.1514843 ,
                    -0.8062826 , -0.69583875, -0.74578637}, .bias = 0.14179966, .n_weights=8},
    };

    // layers
    layer1_t layer1 = {
        .l1_neurons[0] = l1_neurons[0], 
        .l1_neurons[1] = l1_neurons[1], 
        .l1_neurons[2] = l1_neurons[2], 
        .l1_neurons[3] = l1_neurons[3], 
        .l1_neurons[4] = l1_neurons[4], 
        .l1_neurons[5] = l1_neurons[5], 
        .l1_neurons[6] = l1_neurons[6], 
        .l1_neurons[7] = l1_neurons[7], 
        .length=8
    };

    layer2_t layer2 = {
        .l2_neurons[0] = l2_neurons[0], 
        .l2_neurons[1] = l2_neurons[1], 
        .l2_neurons[2] = l2_neurons[2], 
        .length=3
    };

    // network
    neural_net_t neural_net = {
        .layer1 = layer1,
        .layer2 = layer2
    };
    // Start stopwatch

    double start, end;
    start = omp_get_wtime();
    int length = 0;
    while ((length++) <500)
    {
        #pragma omp parallel default(none)  shared(test_data) firstprivate(neural_net) num_threads(2)
        {
            #pragma omp for schedule(static)
            for(int i = 0 ; i < 150 ; i++){
                // neural_net_run(neural_net_t* neural_net, double *data, int len)
                // Process one row of sample data at a time
                // Result is the output from the 3 neurons in the output layer
                double *result = run_neural_net(neural_net, test_data[i] + 1);
                printf("%d %lf %lf %lf -> %d\n", i, *result, result[1], result[2], classify(result, 3));
                
                free(result);
            }
        }
    }
    // Stop stopwatch
    end = omp_get_wtime();
    printf("%lf\n", end-start);

/* USER CODE END */

    return 0;
}

double *run_layer1(layer1_t layer, double *data)
{   
    double *result = (double*) malloc(layer.length*sizeof(double));

    // iterate through neurons
    for (int neuron=0; neuron<layer.length;neuron++)
    {
        result[neuron] = 0.0;
        for(int input = 0; input < layer.l1_neurons[neuron].n_weights; input++){
            
            result[neuron] += layer.l1_neurons[neuron].weights[input] * data[input];
        }
        result[neuron] += layer.l1_neurons[neuron].bias;
        result[neuron] = _activation_func(result[neuron]);
        
    }
    return result;
}

// Activation function (logit) of each neuron
double _activation_func(double val){
    return 1/(1+exp(-val));
}


double *run_layer2(layer2_t layer, double* data)
{
    double *result = (double*) malloc(layer.length*sizeof(double));

    // iterate through neurons
    for (int neuron=0; neuron<layer.length;neuron++)
    {
        result[neuron] = 0.0;
        for(int input = 0; input < layer.l2_neurons[neuron].n_weights ; input++){
            
            result[neuron] += layer.l2_neurons[neuron].weights[input] * data[input];
        }
        result[neuron] += layer.l2_neurons[neuron].bias;
        result[neuron] = _activation_func(result[neuron]);
    }
    return result;
}

double * run_neural_net(neural_net_t neural_net, double *test_data){

    // copy mid 4 rows of test data
    double *data = (double *) malloc(4*sizeof(double));
    memcpy(data, test_data, sizeof(double)*4);

    // Run layer 1
    double *layer1_result = (double*) malloc(neural_net.layer1.length*sizeof(double));
    layer1_result = run_layer1(neural_net.layer1, data);
    
    // Run layer 2
    double *layer2_result = (double*) malloc(neural_net.layer2.length*sizeof(double));
    layer2_result = run_layer2(neural_net.layer2, layer1_result);
    free(layer1_result);

    return layer2_result;
}
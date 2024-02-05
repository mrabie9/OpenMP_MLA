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
#include "../data.h"

typedef struct linked_list linked_list_t;


linked_list_t* new_linked_list();

bool linked_list_append(linked_list_t *list, void *data);

void *linked_list_remove(linked_list_t *list, int index);

bool linked_list_start_iterator(linked_list_t *list);

void *linked_list_get_next(linked_list_t *list);

int linked_list_length(linked_list_t *list);

void *linked_list_get_last(linked_list_t *list);

typedef struct neural_net neural_net_t;

neural_net_t* create_neural_net();

void neural_net_add_layer(neural_net_t *neural_net);

void neural_net_add_neuron(neural_net_t *neural_net, double *weights, int n_weights, double bias);

double * neural_net_run(neural_net_t* neural_net, double *data, int len);


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

/* USER CODE END */

int main(void)
{

//
    int i;

    neural_net_t *neural_net = create_neural_net();

    neural_net_add_layer(neural_net);
    double w_0_0[] = { 0.18284023, -0.8529724 ,  0.9295352 ,  0.27745247};
    neural_net_add_neuron(neural_net, w_0_0,  4, -0.5623624);

    double w_0_1[] = {-0.17880775, -0.42715448,  0.5908963 ,  0.45988828};
    neural_net_add_neuron(neural_net, w_0_1,  4, -0.05714933);

    double w_0_2[] = {-0.48771185, -0.3112061 , -0.3137951 ,  0.5289104 };
    neural_net_add_neuron(neural_net, w_0_2,  4, -0.053803623);

    double w_0_3[] = { 0.24778503,  0.9340235 , -1.4063437 , -1.3005494 };
    neural_net_add_neuron(neural_net, w_0_3,  4, 0.27202815);

    double w_0_4[] = { 0.72132677, -0.12656425, -1.1483048 , -0.083784  };
    neural_net_add_neuron(neural_net, w_0_4,  4, 0.41053805);

    double w_0_5[] = { 0.05532144,  0.47561175, -0.17761162, -1.3145427 };
    neural_net_add_neuron(neural_net, w_0_5,  4, 0.28362706);

    double w_0_6[] = { 0.12644108, -0.6311569 ,  0.03945397, -0.53849036};
    neural_net_add_neuron(neural_net, w_0_6,  4, 0.025350625);

    double w_0_7[] = { 0.21844819,  0.30629316, -0.961491  , -0.46816182};
    neural_net_add_neuron(neural_net, w_0_7,  4, 0.6091357);

    neural_net_add_layer(neural_net);
    double w_1_0[] = {-1.2635437 , -1.316526  ,  0.28543112,  1.3884338 ,  0.45282924,
      1.0371606 ,  0.12748991,  0.6325952 };
    neural_net_add_neuron(neural_net, w_1_0,  8, -0.43309692);

    double w_1_1[] = { 0.497385  , -0.632777  ,  0.38966534, -1.2256211 , -0.19634834,
      0.25377455,  0.6375568 , -0.5464157 };
    neural_net_add_neuron(neural_net, w_1_1,  8, -0.14760242);

    double w_1_2[] = { 0.3835234 ,  0.10146759, -0.32170305, -1.1918751 , -1.1514843 ,
     -0.8062826 , -0.69583875, -0.74578637};
    neural_net_add_neuron(neural_net, w_1_2,  8, 0.14179966);

    // Start stopwatch
    double start, end;
    start = omp_get_wtime();
    int length = 0;
    while((length++)<500)
    {
        double *result;
        for(i = 0 ; i < 150 ; i++){
            // neural_net_run(neural_net_t* neural_net, double *data, int len)
            // Process one row of sample data at a time
            // Result is the output from the 3 neurons in the output layer
            result = neural_net_run(neural_net, test_data[i] + 1, 4);
            printf("%d %lf %lf %lf -> %d\n", i, *result, result[1], result[2], classify(result, 3));
            
            free(result);
        }
    }

    // Stop stopwatch
    end = omp_get_wtime();
    printf("%lf\n", end-start);

/* USER CODE END */

    return 0;
}


struct neural_net{
    linked_list_t *layers;
};

typedef struct{
    linked_list_t* neurons;
}layer_t;


typedef struct{

    double* weights;
    double bias;
    int n_weights;
    

}neuron_t;

neural_net_t* create_neural_net(){

    neural_net_t *neural_net = (neural_net_t*)malloc(sizeof(neural_net_t));
    neural_net->layers = new_linked_list(); // new layer

    return neural_net;

}

void neural_net_add_layer(neural_net_t *neural_net){

    layer_t *layer = malloc(sizeof(layer_t));
    layer->neurons = new_linked_list(); // neurons within the layer
    linked_list_append(neural_net->layers, layer);

}

void neural_net_add_neuron(neural_net_t *neural_net, double *weights, int n_weights, double bias){

    layer_t *last_layer = linked_list_get_last(neural_net->layers);

    neuron_t *neuron  = (neuron_t*)malloc(sizeof(neuron_t));
    neuron->weights = weights;
    neuron->n_weights = n_weights;
    neuron->bias = bias;

    linked_list_append(last_layer->neurons, neuron);

}

// Activation function (logit) of each neuron
double _activation_func(double val){
    return 1/(1+exp(-val));
}

// dot product of input and weights for 1 neuron
double _neuron_evaluate(neuron_t* neuron, double *data){

    int i;
    double result;
    for(i = 0, result = 0 ; i <  neuron->n_weights ; i++){

        result += neuron->weights[i] * data[i];

    }


    return _activation_func(result + neuron->bias);
}


double * neural_net_run(neural_net_t* neural_net, double *data, int len){

    layer_t *layer;
    neuron_t *neuron;
    int i;
    double result;

    // Hold outputs from previous layer (initially = inputs?)
    double *prev_outputs = (double *)malloc(sizeof(double)*len);
    double *next_outputs = NULL;
    
    linked_list_start_iterator(neural_net->layers);

    // Copy mid 4 values from row of sample data into prev_outputs
    memcpy(prev_outputs, data, sizeof(double)*len);

    // Iterate between layers
    while(layer = linked_list_get_next(neural_net->layers)){

        // Point to first layer
        linked_list_start_iterator(layer->neurons);
        result = 0;

        // Hold outputs of neurons
        next_outputs = malloc(sizeof(double) * (linked_list_length(layer->neurons)));
//      next_outputs[linked_list_length(layer->neurons)] = layer->bias;
        i = 0;
        
        // Iterate between neurons within layer
        while(neuron = linked_list_get_next(layer->neurons)){
            
            // output of current neuron by dot product of input and weights then activation function
            next_outputs[i] = _neuron_evaluate(neuron, prev_outputs);
            i++;
        }

        free(prev_outputs);
        prev_outputs = next_outputs;
    }

    return prev_outputs;
}



typedef struct node node_t;

struct node{

    void *data;
    node_t *next;

};


struct linked_list{

    node_t *head;
    node_t *tail;
    node_t *iterator;
    int length;

};


linked_list_t* new_linked_list(){

    linked_list_t *linked_list = (linked_list_t*)malloc(sizeof(linked_list_t));

    linked_list->head = NULL;
    linked_list->iterator = NULL;
    linked_list->tail = NULL;
    linked_list->length = 0;

    return linked_list;

}

bool linked_list_append(linked_list_t *list, void *data){

    node_t *node = (node_t*) malloc(sizeof(node_t));

    node->data = data;
    node->next = NULL;

    if(list->head == NULL){
        list->head = node;
        list->tail = node;
    }else{
        list->tail->next = node;
        list->tail = node;
    }

    list->length++;

}

void *linked_list_remove(linked_list_t *list, int index){


    if(index >= list->length){
        return NULL;
    }

    if(index == 0){

        void *data = list->head->data;
        node_t *node_to_remove = list->head;
        list->head = list->head->next;

        free(node_to_remove);

        if(list->head == NULL){
            list->tail == NULL;
        }

        list->length--;
        return data;

    }

    
    int current_index = 0;
    node_t* node = list->head;

    while(current_index < index - 1){
        current_index++;
        node = node->next;
    }

    node_t* node_to_remove = node->next;
    node->next = node_to_remove->next;
    void *data = node_to_remove->data;

    if(index == list->length - 1){
        list->tail = node;
    }

    free(node_to_remove);
    list->length--;

    return data;
    

}

bool linked_list_start_iterator(linked_list_t *list){
    list->iterator = list->head;
}

// Get next neuron
void *linked_list_get_next(linked_list_t *list){
    
    if(list->iterator == NULL){
        return NULL;
    }

    void *data = list->iterator->data;
    list->iterator = list->iterator->next;
    return data;

}

int linked_list_length(linked_list_t *list){

    return list->length;

}


void *linked_list_get_last(linked_list_t *list){

    return list->tail->data;

}

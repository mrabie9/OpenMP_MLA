/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  /* USER CODE END Header */


  /* Private includes ----------------------------------------------------------*/
  /* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../data.h"
#include <omp.h>

//
// node in decision tree
//
struct Node
{
    // data parameters
    int index;
    float value;

    // child nodes if the node is an internal node
    //int left;
    //int right;
    struct Node *left;
    struct Node *right;

    // node
    int left_node;
    int right_node;

    // node number
    int nNode;
    int father;

    // if the node is a leaf
    float left_leaf;
    float right_leaf;
};


float* get_class_labels(float data[][6], int rows, int cols);



//
// decision trees
//
struct Node* create_node();
struct Node** fit_model(float treeRF[][10][6], int n_estimators);
void grow(struct Node* decision_tree, float treeRF[][6], int nodeNum);

//
// predictions with the decision trees
//
float majority_vote_predict(float* predictions, int n_predictions);
float predict(struct Node* decision_tree, float* row);

void csv_dimensions(float* maxNodesTree, char fn[][100], int n_estimators);
float** create_array_2d(int n, int m);
void destroy_array_2d(float** arr);
float** read_data_2d(FILE* csv, float** data, int rows, int cols);
float*** create_array_3d(float* n, int m, int k, int total);
void destroy_array_3d(float*** arr);
float** read_data_3d(float csv[][10][6], float*** treeRF, float* maxNodesTree, int colsTree, int n_estimators, int k);
double get_accuracy(int n, float* labels, float* prediction);


float tree0(float in[4]) {
    if (in[4] <= 0.8) {
        return 0.0;
    }
    else
    {
        if (in[3] <= 4.95) {
            if (in[4] <= 1.7) {
                return 1.0;
            }
            else {
                return 2.0;
            }
        }
        else {
            return 2.0;
        }
    }
}
    /*
    static int node = 0;
    if (in[(int)vec[node][2]] <= vec[node][3]) {
        if (vec[node][0] == 0.0) {
            return vec[node][4];
        }
        else {
            node++;
            tree1(in, vec);
        }
    }
    else
    {
        node++;
        if (in[3] <= 4.95) {
            if (in[4] <= 1.7) {
                return 1.0;
            }
            else {
                return 2.0;
            }
        }
        else {
            return 2.0;
        }
    }
    */

float tree1(float in[4]) {
    if (in[4] <= (float)0.8) {
        return 0.0;
    }
    else
    {
        if (in[4] <= (float)1.7) {
            if (in[3] <= (float)4.95) {
                return 1.0;
            }
            else {
                if (in[2] <= (float)2.65) {
                    return 2.0;
                }
                else {
                    if (in[2] <= (float)2.75) {
                        return 1.0;
                    }
                    else {
                        return 2.0;
                    }
                }
            }
        }
        else {
            return 2.0;
        }
    }
}

float tree2(float in[4]) {
    if (in[1] <= (float)5.55) {
        if (in[4] <= (float)0.8) {
            return 0.0;
        }
        else 
        {
            return 1.0;
        }
        
    }
    else
    {
        if (in[3] <= (float)4.75) {
            return 0.0;
        }
        else {
            if (in[4] <= (float)1.65) {
                if (in[2] <= (float)2.95) {
                    return 2.0;
                }
                else {
                    return 1.0;
                }
            }
            else {
                return 2.0;
            }
        }
    }
}

float tree3(float in[4]) {
    if (in[1] <= (float)5.55) {
        if (in[2] <= (float)2.85) {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    }
    else
    {
        if (in[2] <= (float)2.65) {
            if (in[2] <= (float)2.35) {
                if (in[4] <= (float)1.25) {
                    return 1.0;
                }
                else {
                    return 2.0;
                }
            }
            else {
                return 2.0;
            }
        }
        else {
            if (in[4] <= (float)1.25) {
                return 1.0;
            }
            else {
                return 2.0;
            }
        }
    }
}



float tree4(float in[4]) {
    if (in[4] <= 0.8) {
        return 0.0;
    }
    else
    {
        if (in[4] <= (float) 1.7) {
            if (in[3] <= 4.95) {
                return 1.0;
            }
            else {
                if (in[4] <= 1.55) {
                    return 2.0;
                }
                else {
                    return 1.0;
                }
            }
        }
        else {
            return 2.0;
        }
    }
}

float tree5(float in[4]) {
    if (in[4] <= 0.8) {
        return 0.0;
    }
    else
    {
        if (in[4] <= (float)4.75) {
            return 1.0;
        }
        else {
           
            if (in[2] <= 2.75) {
                if (in[4] <= 1.7) {
                    if (in[1] <= 6.05) {
                        if (in[2] <= 2.45) {
                            return 2.0;
                        }
                        else {
                            return 1.0;
                        }
                    }
                    else {
                        return 2.0;
                    }
                }
                else {
                    return 2.0;
                }
            }
            else {
                if (in[1] <= 6.05) {
                    if (in[2] <= 2.45) {
                        return 2.0;
                    }
                    else {
                        return 1.0;
                    }
                }
                else {
                    return 2.0;
                }
            }
            
        }
    }
}


float tree6(float in[4]) {
    if (in[4] <= (float)1.7) {
        if (in[3] <= (float)2.6) {
            return 0.0;
        }
        else
        {
            if (in[2] <= (float)2.25) {
                if (in[4] <= (float)1.25) {
                    return 1.0;
                }
                else
                {
                    return 2.0;
                }
            }
            else
            {
                if (in[1] <= (float)6.2) {
                    return 1.0;
                }
                else
                {
                    if (in[1] <= (float)6.35) {
                        if (in[3] <= (float)4.9) {
                            return 1.0;
                        }
                        else
                        {
                            return 2.0;
                        }
                    }
                    else
                    {
                        return 1.0;
                    }
                }
            }
        }
    }
    else
    {
        return 2.0;
    }
}

float tree7(float in[4]) {
    if (in[3] <= 4.75) {
        if (in[3] <= 2.6) {
            return 0.0;
        }
        else {
            return 1.0;
        }
    }
    else
    {
        if (in[3] <= (float)4.85) {
            if (in[2] <= 2.9) {
                if (in[1] <= 6.5) {
                    return 2.0;
                }
                else {
                    return 1.0;
                }
            }
            else {
                return 2.0;
            }
        }
        else {
            return 2.0;
        }
    }
}

float tree8(float in[4]) {
    if (in[4] <= (float)1.7) {
        if (in[1] <= (float)5.45) {
            if (in[3] <= (float)2.6) {
                return 0.0;
            }
            else {
                return 1.0;
            }
        }
        else {
            if (in[3] <= (float)2.55) {
                return 0.0;
            }
            else {
                if (in[2] <= (float)2.25) {
                    return 2.0;
                }
                else {
                    if (in[3] <= (float)5) {
                        return 1.0;
                    }
                    else {
                        if (in[1] <= (float)6.5) {
                            return 1.0;
                        }
                        else {
                            return 2.0;
                        }
                    }
                }
            }
        }
    }
    else
    {
        return 2.0;
    }
}

float tree9(float in[4]) {
    if (in[3] <= (float)2.6) {
        return 0.0;
    }
    else
    {
        if (in[3] <= (float)4.75) {
            return 1.0;
        }
        else {
            if (in[2] <= (float)2.75) {
                if (in[4] <= (float)1.7) {
                    return 1.0;
                }
                else {
                    return 2.0;
                }
            }
            else {
                if (in[1] <= (float)6.85) {
                    return 1.0;
                }
                else {
                    if (in[2] <= (float)3.15) {
                        if (in[4] <= (float)1.8) {
                            return 1.0;
                        }
                        else {
                            return 2.0;
                        }
                    }
                    else {
                        return 2.0;
                    }

                }
            }
        }
    }
}

float *myPredict(float in[4]){
    float *result = (double*) malloc(10*sizeof(float));
    result[0] = tree0(in);
    result[1] = tree1(in);
    result[2] = tree2(in);
    result[3] = tree3(in);
    result[4] = tree4(in);
    result[5] = tree5(in);
    result[6] = tree6(in);
    result[7] = tree7(in);
    result[8] = tree8(in);
    result[9] = tree9(in);
    return result;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    int rows = 151 - 1;
    int cols = 6;

    // dimensions of csv file
    int n_estimators = 10; // n_estimators = number of trees in the foreset
    //int rowsTree = 8-1;
    int colsTree = 6;
    // float* maxNodesTree = malloc(n_estimators * sizeof(float));
    float maxNodesTree[10] = { 3, 5, 5, 10, 4, 8, 7, 5, 7, 7 };

    // total number of rows
    int totalRows = 0;
    //  int maxMaxNodesTree = 10;
    int i;

    for (i = 0; i < n_estimators; i++) {
        totalRows = maxNodesTree[i] + totalRows;
    }


    // allocate space in memory to load all csvs
    float*** treeRF = create_array_3d(maxNodesTree, colsTree, n_estimators, totalRows);
    int k;
    // read data into memory
    // for (k = 0; k < n_estimators; k++) {
    //     read_data_3d(motherFucking3dVec, treeRF, maxNodesTree, colsTree, n_estimators, k);
    // }

    // struct Node** rf = fit_model(motherFucking3dVec, n_estimators);

    double accuracy;
    float sample[6];
    float *predictions;
    char send_string[300];
    float mypre;
    // Start stopwatch
    double start, end;
    start = omp_get_wtime();    
    int loop = 0;
    while((loop++)<500){
        #pragma omp parallel default(none) private(predictions, i) \ 
                                            firstprivate(test_data, n_estimators) num_threads(32)
        {
            #pragma omp for schedule(guided)
            for (int j = 0; j < 150; j++)
            {
            printf("%d ->", j);

                for (i = 0; i < 4; i++) {
                    printf("%f, ", test_data[j][i]);
                }

                printf(" -> ");

                for (i = 0; i < n_estimators; i++)
                {   
                    predictions = myPredict(test_data[j]);
                    printf("%.5f,", predictions[i]);
                }
                printf("-> %f \n", majority_vote_predict(predictions, n_estimators));
                free(predictions);
            }
        }
    }
    // Stop stopwatch
    end = omp_get_wtime();
    printf("%lf\n", end-start);
}


//
// Dataset Cross Validation for preliminary evaluation of the random forest on the available test data
//
float* get_class_labels(float data[][6], int rows, int cols)
{
    float* class_labels = malloc(rows * sizeof(float));
    int i;
    for (i = 0; i < rows; i++)
    {
        float* row = data[i];
        class_labels[i] = row[cols - 1];
    }
    return class_labels;
}


//
// build up a forest of random decision trees based on the given parameters and fit to the training data
//
struct Node** fit_model(float treeRF[][10][6], int n_estimators)
{
    // father node is created here!
    struct Node** trees = (struct Node**)malloc(sizeof(struct Node) * n_estimators);
    int nodeNum = 0;
    int k;
    for (k = 0; k < n_estimators; k++) {
        printf("---------Loading tree %d ------------\n", k);
        struct Node* root = create_node();
        root->left_node = treeRF[k][0][0];
        root->right_node = treeRF[k][0][1];
        root->index = treeRF[k][0][2];
        root->value = treeRF[k][0][3];
        root->nNode = nodeNum;
        root->father = 1;
        grow(root, treeRF[k], nodeNum);
        trees[k] = root;
    }
    return trees;
}

//
// tree node "constructor"
//
struct Node* create_node()
{
    int* i = malloc(sizeof(int));
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->left = NULL; // true => left
    newNode->right = NULL; // false => right
    newNode->father = -1;
    *i = 1;
    newNode->right_node = -1; // end of tree in left = leaf
    newNode->left_node = -1; // end of tree in right = leaf
    newNode->right_leaf = -1; // end of tree in left = leaf
    newNode->left_leaf = -1; // end of tree in right = leaf
    newNode->nNode = -1; // end of tree in right = leaf
    newNode->index = -1; // feature_parameter_index (petal/sepal width/length) > {0-4}
    newNode->value = -1; // value corresponding to parameter_index
    return newNode;
}


//
// grow of a decision tree:
// Basicaly it start with the left node and stores the last node address.
// When the leaf node (last node) is done, the algorithm sets the flag leaf_right/leaf_left to 0;
// It starts going one node back, cheaking its leaf flags. If the flag is on, it means we should creat a left/right node, and so set it to 0.
// The algorithm ends when it reaches the root node and all nodes leaf flags are down.
// The parameters loaded to each tree is into the csv file, each line contain each node params, so the line number (and also the node number, so 'nodeNum') is stored into the tree param as nNode. So when the algorithm are cheacking the leaf node flag, the nNode param is used to acces the csv file params.
//
void grow(struct Node* decision_tree, float treeRF[][6], int nodeNum)
{
    //printf("NodeNum %d\n",nodeNum);
    if (decision_tree->left_node == 0)
    {
        //printf("leaf_left DONE! NodeNum = %d\n",decision_tree->nNode);
        decision_tree->left_leaf = treeRF[decision_tree->nNode][4];
    }
    else { // create node
        // store last node adsress
        decision_tree->left_node = 0;
        decision_tree->left = create_node();
        nodeNum++;
        decision_tree->left->nNode = nodeNum;
        decision_tree->left->left_node = treeRF[nodeNum][0];
        decision_tree->left->right_node = treeRF[nodeNum][1];
        decision_tree->left->index = treeRF[nodeNum][2];
        decision_tree->left->value = treeRF[nodeNum][3];
        //printf("I'm doing the grow_left NodeNum = %d\n",nodeNum);
        grow(decision_tree->left, treeRF, nodeNum);
    }
    if (decision_tree->right_node == 0) // create node == null
    {
        //printf("leaf_right DONE! NodeNum = %d\n",decision_tree->nNode);
        decision_tree->right_leaf = treeRF[decision_tree->nNode][5];
    }
    else { // create node
        decision_tree->right_node = 0;
        decision_tree->right = create_node();
        nodeNum++;
        decision_tree->right->nNode = nodeNum;
        decision_tree->right->left_node = treeRF[nodeNum][0];
        decision_tree->right->right_node = treeRF[nodeNum][1];
        decision_tree->right->index = treeRF[nodeNum][2];
        decision_tree->right->value = treeRF[nodeNum][3];
        //printf("I'm doing the grow_right NodeNum = %d\n",nodeNum);
        grow(decision_tree->right, treeRF, nodeNum);
    }
    if (decision_tree->left_node == 0)
    {
        //printf("leaf_left DONE! NodeNum = %d\n",decision_tree->nNode);
        decision_tree->left_leaf = treeRF[decision_tree->nNode][4];
    }
    else { // create node
        // store last node adsress
        decision_tree->left_node = 0;
        decision_tree->left = create_node();
        nodeNum++;
        decision_tree->left->nNode = nodeNum;
        decision_tree->left->left_node = treeRF[nodeNum][0];
        decision_tree->left->right_node = treeRF[nodeNum][1];
        decision_tree->left->index = treeRF[nodeNum][2];
        decision_tree->left->value = treeRF[nodeNum][3];
        //printf("I'm doing the grow_left NodeNum = %d\n",nodeNum);
        grow(decision_tree->left, treeRF, nodeNum);
    }
    if (decision_tree->right_node == 0) // create node == null
    {
        //printf("leaf_right DONE! NodeNum = %d\n",decision_tree->nNode);
        decision_tree->right_leaf = treeRF[decision_tree->nNode][5];
    }
    else { // create node
        decision_tree->right_node = 0;
        decision_tree->right = create_node();
        nodeNum++;
        decision_tree->right->nNode = nodeNum;
        decision_tree->right->left_node = treeRF[nodeNum][0];
        decision_tree->right->right_node = treeRF[nodeNum][1];
        decision_tree->right->index = treeRF[nodeNum][2];
        decision_tree->right->value = treeRF[nodeNum][3];
        //printf("I'm doing the grow_right NodeNum = %d\n",nodeNum);
        grow(decision_tree->right, treeRF, nodeNum);
    }
    if (decision_tree->left_node == 0 && decision_tree->right_node == 0) { //if this is the root and leaf left and right are done > return
        if (decision_tree->father == 1) {
            //printf("DONE\n");
            return;
        }
    }
    return;
    //grow(decision_tree->addressLastNode, treeRF, nodeNum);
}

//
// predict by propagating the trained tree
//
float predict(struct Node* decision_tree, float* row)
{
    //printf("decision_tree %f\n", decision_tree->left_leaf);
    //printf("decision_tree %f\n", decision_tree->right->right_leaf);
    //printf("decision_tree %f\n", decision_tree->right->left->right_leaf);
    if (row[decision_tree->index] <= decision_tree->value)
    {
        if (decision_tree->left != NULL)
        {
            return predict(decision_tree->left, row);
        }
        else
        {
            return decision_tree->left_leaf;
        }
    }
    else {
        if (decision_tree->right != NULL)
        {
            return predict(decision_tree->right, row);
        }
        else
        {
            return decision_tree->right_leaf;
        }
    }
}

//
// determines the prediction based on a majority vote from an array of trees (forest)
// currently only implemented for {0,1,2} classification
//
float majority_vote_predict(float* predictions, int n_predictions)
{
    int zeroes = 0;
    int ones = 0;
    int twos = 0;
    int i;
    for (i = 0; i < n_predictions; i++)
    {
        if (((int)predictions[i]) == 0) zeroes++;
        else if (((int)predictions[i]) == 1) ones++;
        else if (((int)predictions[i]) == 2) twos++;
    }
    if (zeroes >= ones && zeroes >= twos) {
        //        if(verbose) printf("\nmajority vote: 0\n");
        return 0;
    }
    else if (ones >= zeroes && ones >= twos) {
        //        if(verbose) printf("\nmajority vote: 1\n");
        return 1;
    }
    else {
        //        if(verbose) printf("\nmajority vote: 2\n");
        return 2;
    }
}


//
// flag for verbose output
//
int verbose = 0;

// csv file dimentions
void csv_dimensions(float* maxNodesTree, char fn[][100], int n_estimators)
{
    int rows_count = 0;
    int i, c;
    FILE* file;
    //float* row_dimention = malloc(n_estimators * sizeof(float));
    for (i = 0; i < n_estimators; i++) {
        rows_count = 0;
        file = fopen(fn[i], "r");
        for (c = getc(file); c != EOF; c = getc(file)) {
            if (c == '\n') {// Increment count if this character is newline
                rows_count++;
            }
        }
        //printf("The file has %d lines\n ", rows_count-1);
        maxNodesTree[i] = rows_count - 1;
    }
    return;
}

//
// memory management
//

// create a 2D array equivalent to a nxm matrix
//
float** create_array_2d(int n, int m)
{
    float* values = calloc(m * n, sizeof(float));
    float** rows = malloc(n * sizeof(float*));
    int i;
    for (i = 0; i < n; i++) {
        rows[i] = values + i * m;
    }
    return rows;
}

//
// free any 2D array
//
void destroy_array_2d(float** arr)
{
    free(*arr);
    free(arr);
}

//
// parse the input 2D csv file into memory
//
float** read_data_2d(FILE* csv, float** data, int rows, int cols) {
    float temp;
    int i;
    int j;
    if (verbose) printf("\nloading data from csv...\n\n");
    fscanf(csv, "%*[^\n]\n"); // to read and discard the first line
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(csv, "%f", &temp);
            data[i][j] = temp;
            fscanf(csv, ",");
            if (verbose) printf("data = %f \n", data[i][j]);
        }
        fscanf(csv, "0x0a"); // read the end of line in a .csv
        if (verbose) printf("\n");
    }
    fclose(csv);
    return 0;
}


// create a 3D array equivalent to a nxmxk matrix
//
float*** create_array_3d(float* n, int m, int k, int total)
{
    float* values = calloc(m * total, sizeof(float));
    float** nodes = malloc(total * sizeof(float*)); //rows
    float*** treeRF = malloc(k * sizeof(float**));
    int i;
    int j;
    for (i = 0; i < total; i++) {
        nodes[i] = values + i * m;
    }
    int AddressNode = 0;
    for (j = 0; j < k; j++) {
        treeRF[j] = nodes + AddressNode; // deal with it
        AddressNode = n[j] + AddressNode;
    }
    return treeRF;
}

//
// free any 3D array
//
void destroy_array_3d(float*** arr)
{
    free(**arr);
    free(*arr);
    free(arr);
}

//
// parse the input 3D csv file into memory
//
float** read_data_3d(float csv[][10][6], float*** treeRF, float* maxNodesTree, int colsTree, int n_estimators, int k) {
    float temp;
    int i;
    int j;
    if (verbose) printf("\nloading data from csv...\n\n");
    // fscanf(csv, "%*[^\n]\n"); // to read and discard the first line
    for (i = 0; i < maxNodesTree[k]; i++) {
        for (j = 0; j < colsTree; j++) {
            // fscanf(csv, "%f", &temp);
            treeRF[k][i][j] = csv[k][i][j];
            //printf("treeRF = %f \n", treeRF[k][i][j]);
            // fscanf(csv, ",");
            if (verbose) printf("treeRF = %f \n", treeRF[k][i][j]);
        }
        // fscanf(csv,"0x0a"); // read the end of line in a .csv
        if (verbose) printf("\n");
    }
    //fclose(csv[k]);
    return 0;
}

//
// performance metrics calculation utilities
//
double get_accuracy(int n, float* labels, float* prediction)
{
    int correct = 0;
    int a = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        a = prediction[i] - labels[i];
        if (a == 0) correct++;
    }
    return (correct * 1.0 / n * 1.0) * 1.0;
}




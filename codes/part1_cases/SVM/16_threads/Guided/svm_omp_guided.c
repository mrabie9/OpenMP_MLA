#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "../../data.h"

// #define NUM_THREADS 4

float svm_compute(float sample[], int n_svs, float svs[][2], float alphas[], float bias){
	
	int i = 0;
	float acc_sum = 0;
    #pragma omp simd 
    for(i = 0 ; i < n_svs ; i++){

        acc_sum += ((sample[0] * svs[i][0] + sample[1]*svs[i][1])*alphas[i]);

    }
	return acc_sum + bias;
}

typedef enum{
    SET = 0, VERS, VIRG
} final_classes_t;

final_classes_t classify(float vals[]){

    int flower[3] = {0, 0, 0};

    if(vals[0] > 0){
        flower[0] += 1;
    }
    else{
        flower[1] += 1;
    }

    if(vals[1] > 0){
        flower[0] += 1;
    }
    else{
        flower[2] += 1;
    }
    if(vals[2] > 0){
        flower[1] += 1;
    }
    else{
        flower[2] += 1;
    }

    int i;
    int final_class = 0;
    int vote_count = flower[0];
    for(i = 1 ; i < 3 ; i++){

        if(flower[i] > vote_count){
            vote_count = flower[i];
            final_class = i;
        }

    }

    return final_class;

}

int main(){

    float results[3];
    double start, end;

    start = omp_get_wtime();
    int loop = 0;
    while ((loop++) <500)
    {
        // omp_set_num_threads(NUM_THREADS);
        #pragma omp parallel default(none)  private(results) \
                                            firstprivate(samples, set_vers_svs, set_vers_alphas, set_vers_bias, \
                                                        versi_virg_svs, versi_virg_alphas, versi_virg_bias,\
                                                        set_virg_svs, set_virg_alphas, set_virg_bias) num_threads(16)
        {   
            
            #pragma omp for schedule(guided)
            for(int i = 0 ; i < DATA_SIZE ; i++){
                
                results[0] = svm_compute(samples[i], 2, set_vers_svs, set_vers_alphas, set_vers_bias);
                results[1] = svm_compute(samples[i], 2, set_virg_svs, set_virg_alphas, set_virg_bias);
                results[2] = svm_compute(samples[i], 16, versi_virg_svs, versi_virg_alphas, versi_virg_bias);

                int final_class = classify(results);
                printf("%3d: %5f, %5f, %5f\nFinal class -> %d\n",
                    i, results[0], results[1], results[2], final_class);
            }
        }

    end = omp_get_wtime();

    printf("%lf\n", end-start);
    }

}
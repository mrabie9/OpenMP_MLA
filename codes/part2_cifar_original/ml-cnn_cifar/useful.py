import subprocess
import os
import time
from datetime import datetime
import numpy as np

wdir = "C:\WSD530\OpenMP/"
app = "codes\part2_cifar_original\ml-cnn_cifar/"
program = "app"
num_threads = "4"

# mla_programs = ["SVM", "NeuralNet", "RandomForest"]

def rebuild():
    print("Rebuilding...")
    compile = subprocess.run("cd " + wdir + app + "&& make clean", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()
    compile = subprocess.run("cd " + wdir + app + "&& make", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()
    print("Rebuilt.")

def main():
    global app

    # Rebuild programs
    rebuild()

    # Store runtimes in file
    
    output = wdir + "data/" + "CMSIS_NN_" + num_threads + ".txt"
    exec_times = wdir + "data/" + "CMSIS_NN_"  + num_threads + "_results.txt"

    with open(exec_times, 'w') as file:
        file.close()

    for i in range(1):

        # print("Collecting " + program + " data...")
        # print("Running subprocess: " + wdir+app + program + ".\\" + program + "_omp")
        log = subprocess.run(wdir+app + "/.\\" + "app", shell=True, capture_output=True, text=True)
        print("Done. Storing info...")
        with open(output, 'w') as file:
            file.write(log.stdout)
            file.close()
        print("Completed " + program )

        # with open(output, 'r') as file:
        #     lines = file.readlines()
        #     file.close()
        
        # if lines:
        #     with open(exec_times, 'a') as file:
        #         file.write(lines[-1])
        #         file.close()
        # else:
        #     print("No lines at i = " + str(i))
        # print("Execution time: " + lines[-1])
        

main()
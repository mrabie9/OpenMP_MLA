import subprocess
import os
import time
from datetime import datetime
import numpy as np

wdir = "C:\WSD530\OpenMP/"
app = "codes/part1_cases/"
program = "RandomForest"
num_threads = "4"

# mla_programs = ["SVM", "NeuralNet", "RandomForest"]

def rebuild():
    print("Rebuilding...")
    compile = subprocess.run("cd " + wdir + app + program + "&& make clean", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()
    compile = subprocess.run("cd " + wdir + app + program + "&& make", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()
    print("Rebuilt.")

def main():
    global app

    # Rebuild programs
    rebuild()

    # Store runtimes in file
    
    output = wdir + "data/" + program + "_omp" + num_threads + ".txt"
    exec_times = wdir + "data/" + program + "_omp" + num_threads + "_results.txt"

    with open(exec_times, 'w') as file:
        file.close()

    for i in range(500):

        # print("Collecting " + program + " data...")
        # print("Running subprocess: " + wdir+app + program + ".\\" + program + "_omp")
        log = subprocess.run(wdir+app + program + ".\\" + "rf" + "_omp", shell=True, capture_output=True, text=True)
        with open(output, 'w') as file:
            file.write(log.stdout)
            file.close()
        # print("Completed " + program )

        with open(output, 'r') as file:
            lines = file.readlines()
            file.close()
        with open(exec_times, 'a') as file:
            file.write(lines[-1])
            file.close()
        # print("Execution time: " + lines[-1])
        

main()
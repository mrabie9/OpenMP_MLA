import subprocess
import os
import time
from datetime import datetime
import numpy as np

wdir = "C:\WSD530\OpenMP/"
app = "codes/part1_cases/"
# program = "svm"

mla_programs = ["SVM", "NeuralNet", "RandomForest"]

def rebuild():
    print("Rebuilding programs")
    compile = subprocess.run("cd " + wdir + app + "&& make clean", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()
    compile = subprocess.run("cd " + wdir + app + "&& make", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()

def main():
    global app

    # Rebuild programs
    rebuild()

    # Store runtimes in file
    for mla in mla_programs:
        app = "codes/part1_cases/" + f"{mla}/"
        program = mla
        output = wdir + "data/" + program + ".txt"
        exec_times = wdir + "data/" + program + "_results.txt"

        # Overwrite files
        with open(output, 'w') as file:
            file.close()
        with open(exec_times, 'w') as file:
            file.close() 

        print("Collecting " + program + " data")
        print("Running subprocess: " + wdir+app + ".\\" + program)
        for i in range(100):
            # Run the executable 
            f = open(output, "w")
            log = subprocess.run(wdir+app + ".\\" + program, shell=True, capture_output=True, text=True)
            
            f.write(log.stdout)
            f.close()
            with open(output, 'r') as file:
                lines = file.readlines()
                file.close()

            with open(exec_times, 'a') as file:
                file.write(lines[-1])
                
        file.close()
        print("Completed " + program )

main()
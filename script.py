import subprocess
import os
import time
from datetime import datetime
import numpy as np

program_par = "parallel"
num_threads = "2"
matrix_size = "250"
program_seq = "sequential" # comment/uncomment to toggle between programs
wdir = "C:\WSD530\CW1\Task1/"

def main():
    print("Compiling programs")
    compile = subprocess.run("cd " + wdir + "Code/" + "&& make clean", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()
    compile = subprocess.run("cd " + wdir + "Code/" "&& make", shell=True, capture_output=True, text=True)
    if compile.stderr:
        print(compile.stderr)
        exit()

    program = program_par # Select program to run
    # Store runtimes in file
    f = open(wdir + "Data/" + program + "_" + num_threads + "_" + matrix_size + "_results.txt", "w")
    print("Collecting " + program + " data")
    for i in range(100):
        # Run the executable 
        log = subprocess.run(wdir + "Code/" + ".\\" + program, shell=True, capture_output=True, text=True)
        f.write(log.stdout)
    f.close()
    print("Completed " + program )

    # Repeat for sequential code
    program = program_seq
    f = open(wdir + "Data/" + program + "_" + num_threads + "_" + matrix_size + "_results.txt", "w")
    print("Collecting " + program + " data")
    for i in range(100):
        log = subprocess.run(wdir + "Code/" + ".\\" + program, shell=True, capture_output=True, text=True)
        f.write(log.stdout)
    f.close()
    print("Completed " + program)

main()
import subprocess
import os
import time
from datetime import datetime
import numpy as np

wdir = "C:\WSD530\OpenMP/codes/part1_cases/"

def main():
    global app
    programs = ["RandomForest/", "SVM/"] # ["NeuralNet/", "RandomForest/", "SVM/"]
    for program in programs:
        print("python -u " + wdir + program + "script.py")
        campaign_start_time = time.time()
        log = subprocess.run("python -u " + wdir + program + "script.py", shell=True, capture_output=True, text=True)
        print(log.stdout)
        if "Error" in log.stdout or "Error" in log.stderr:
            print(log.stderr)
        print("\n" + program[:-1] + " time taken: " + str(round(time.time() - campaign_start_time,2)) + "s")
main()
all: SVM.elf

SVM.elf: omp.c data.h
	gcc data.h omp.c -o SVM_omp -fopenmp -g
	
clean:
	rm -f SVM.exe
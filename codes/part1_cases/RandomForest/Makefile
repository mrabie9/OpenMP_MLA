all: rf_omp.elf

rf_omp.elf: rf_omp.c data.h
	gcc data.h rf_omp.c -o rf_omp -fopenmp -g
	
clean:
	rm -f rf_omp.exe
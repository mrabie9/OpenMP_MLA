all: base 2_threads 4_threads 8_threads 16_threads 32_threads

base: rf.exe
2_threads: rf_omp_static2.exe rf_omp_guided2.exe rf_omp_dynamic2.exe
4_threads: rf_omp_static4.exe rf_omp_guided4.exe rf_omp_dynamic4.exe
8_threads: rf_omp_static8.exe rf_omp_guided8.exe rf_omp_dynamic8.exe
16_threads: rf_omp_static16.exe rf_omp_guided16.exe rf_omp_dynamic16.exe
32_threads: rf_omp_static32.exe rf_omp_guided32.exe rf_omp_dynamic32.exe

## base
rf.exe: base/main.c data.h
	gcc data.h base/main.c -o base/rf -fopenmp -g -w
	gcc -O3 data.h base/main.c -o base/rf_O3 -fopenmp -g -w

## 2 threads
rf_omp_static2.exe: 2_threads/static/rf_omp_static.c data.h
	gcc data.h 2_threads/static/rf_omp_static.c -o 2_threads/static/rf_omp_static2 -fopenmp -g -w
	
rf_omp_guided2.exe: 2_threads/guided/rf_omp_guided.c data.h
	gcc data.h 2_threads/guided/rf_omp_guided.c -o 2_threads/guided/rf_omp_guided2 -fopenmp -g -w
	
rf_omp_dynamic2.exe: 2_threads/Dynamic/rf_omp_dynamic.c data.h
	gcc data.h 2_threads/Dynamic/rf_omp_dynamic.c -o 2_threads/Dynamic/rf_omp_dynamic2 -fopenmp -g -w

## 4 threads
rf_omp_static4.exe: 4_threads/static/rf_omp_static.c data.h
	gcc data.h 4_threads/static/rf_omp_static.c -o 4_threads/static/rf_omp_static4 -fopenmp -g -w
	
rf_omp_guided4.exe: 4_threads/guided/rf_omp_guided.c data.h
	gcc data.h 4_threads/guided/rf_omp_guided.c -o 4_threads/guided/rf_omp_guided4 -fopenmp -g -w
	
rf_omp_dynamic4.exe: 4_threads/Dynamic/rf_omp_dynamic.c data.h
	gcc data.h 4_threads/Dynamic/rf_omp_dynamic.c -o 4_threads/Dynamic/rf_omp_dynamic4 -fopenmp -g -w	
	
## 8 threads
rf_omp_static8.exe: 8_threads/static/rf_omp_static.c data.h
	gcc data.h 8_threads/static/rf_omp_static.c -o 8_threads/static/rf_omp_static8 -fopenmp -g -w
	
rf_omp_guided8.exe: 8_threads/guided/rf_omp_guided.c data.h
	gcc data.h 8_threads/guided/rf_omp_guided.c -o 8_threads/guided/rf_omp_guided8 -fopenmp -g -w
	
rf_omp_dynamic8.exe: 8_threads/Dynamic/rf_omp_dynamic.c data.h
	gcc data.h 8_threads/Dynamic/rf_omp_dynamic.c -o 8_threads/Dynamic/rf_omp_dynamic8 -fopenmp -g -w
	
## 16 threads
rf_omp_static16.exe: 16_threads/static/rf_omp_static.c data.h
	gcc data.h 16_threads/static/rf_omp_static.c -o 16_threads/static/rf_omp_static16 -fopenmp -g -w
	
rf_omp_guided16.exe: 16_threads/guided/rf_omp_guided.c data.h
	gcc data.h 16_threads/guided/rf_omp_guided.c -o 16_threads/guided/rf_omp_guided16 -fopenmp -g -w
	
rf_omp_dynamic16.exe: 16_threads/Dynamic/rf_omp_dynamic.c data.h
	gcc data.h 16_threads/Dynamic/rf_omp_dynamic.c -o 16_threads/Dynamic/rf_omp_dynamic16 -fopenmp -g -w
	
## 32 threads
rf_omp_static32.exe: 32_threads/static/rf_omp_static.c data.h
	gcc data.h 32_threads/static/rf_omp_static.c -o 32_threads/static/rf_omp_static32 -fopenmp -g -w
	
rf_omp_guided32.exe: 32_threads/guided/rf_omp_guided.c data.h
	gcc data.h 32_threads/guided/rf_omp_guided.c -o 32_threads/guided/rf_omp_guided32 -fopenmp -g -w
	
rf_omp_dynamic32.exe: 32_threads/Dynamic/rf_omp_dynamic.c data.h
	gcc data.h 32_threads/Dynamic/rf_omp_dynamic.c -o 32_threads/Dynamic/rf_omp_dynamic32 -fopenmp -g -w
	
clean:
	rm -f base/rf base/rf_O3
	rm -f non_ll/rf_nonll non_ll/rf_nonll_O3
	rm -f 2_threads/static/rf_omp_static2 2_threads/dynamic/rf_omp_dynamic2 2_threads/guided/rf_omp_guided2
	rm -f 4_threads/static/rf_omp_static4 4_threads/dynamic/rf_omp_dynamic4 4_threads/guided/rf_omp_guided4
	rm -f 8_threads/static/rf_omp_static8 8_threads/dynamic/rf_omp_dynamic8 8_threads/guided/rf_omp_guided8
	rm -f 16_threads/static/rf_omp_static16 16_threads/dynamic/rf_omp_dynamic16 16_threads/guided/rf_omp_guided16
	rm -f 32_threads/static/rf_omp_static32 32_threads/dynamic/rf_omp_dynamic32 32_threads/guided/rf_omp_guided32
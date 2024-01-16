all: NeuralNet.elf SVM.elf RandomForest.elf

NeuralNet.elf: NeuralNet/main.c 
	gcc NeuralNet/data.h NeuralNet/main.c -o NeuralNet/NeuralNet -fopenmp -g
	
SVM.elf: SVM/main.c 
	gcc SVM/data.h SVM/main.c -o SVM/SVM -fopenmp -g	
	
RandomForest.elf: RandomForest/main.c 
	gcc RandomForest/data.h RandomForest/main.c -o RandomForest/RandomForest -fopenmp -g
	
clean:
	rm -f NeuralNet/NeuralNet.exe SVM/SVM.exe RandomForest/RandomForest.exe
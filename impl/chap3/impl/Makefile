MNIST_DATASET_DIR=../dataset/

run: main.cpp MNISTReader.o
	g++ main.cpp ./MNISTReader.o -o ./bin/main
	./bin/main $(MNIST_DATASET_DIR)
	
clean: ./bin/main
	rm ./bin/main ./bin/MNISTReader.o

MNISTReader.o: MNISTReader.cpp MNISTReader.hpp
	g++ -c MNISTReader.cpp 

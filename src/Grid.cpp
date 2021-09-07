/**
 * \file Grid.cpp
 * \brief definition of getGrid function
 * \date 07/09/2021
 * \author Aki Schmatzler
 */


#include "Grid.hpp"

int** getGrid (char* filename, int* X, int* Y) {
	
	std::ifstream file;
	file.open(filename);

	if (!file.is_open()) {
		std::cout << "Could not open the file " << filename << std::endl;
		std::cout << "Program terminating.\n";
		exit(EXIT_FAILURE);
	}
	int value = 0;

	//getting size of the grid
	file >> *X; 
	file >> *Y; 
	std::cout << *X << " " << *Y << std::endl;

	//allocation of 2d array for the grid
	int ** ptr = new int*[*X];
	for(int i = 0; i < *X; i++) {
		ptr[i] = new int[*Y];
	}

	//filling the array
	for (int i = 0; i<(*X)*(*Y); i++) {
		if (!file.good()) {
			std::cout << "Problem while reading, aborting.\n";
			exit(EXIT_FAILURE);
		}

		file >> value;
		ptr[(int)i/(*Y)][(int)i%(*Y)] = value;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	
	//printing the array to standard output
	for (int i = 0; i<(*X); i++) {
		for (int j = 0; j<(*Y); j++) {
			std::cout << ptr[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return ptr;
}


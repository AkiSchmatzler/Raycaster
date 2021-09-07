#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Player.hpp"
#include "Rays.hpp"

using namespace sf;
#define MAX_ARR 100
#define SIZE_SQUARE 64


int** getGrid (char* filename, int* X, int* Y);


int main () {

	
	char filename[MAX_ARR];

	std::cout << "Please enter the path of the file containing the grid info." << std::endl;
	std::cin >> filename;
	std::cout << "Name of the file is " << filename << std::endl;

	int X, Y;
	int** grid = getGrid(filename, &X, &Y);
 
	RenderWindow window (VideoMode (SIZE_SQUARE*Y, SIZE_SQUARE*X), "raycasting");
	window.setFramerateLimit(60); 

	RectangleShape rects[X*Y];
	int counterRect = 0;
	for (int i = 0; i<X; i++) {
		for (int j = 0; j<Y; j++) {
			rects[counterRect] = RectangleShape(Vector2f(SIZE_SQUARE, SIZE_SQUARE));
			rects[counterRect].setPosition(Vector2f(SIZE_SQUARE*j, SIZE_SQUARE*i));
			if (grid[i][j] == 1)
				rects[counterRect].setFillColor(Color::Blue);
			else if (grid[i][j] == 3)
				rects[counterRect].setFillColor(Color::Red);
			else rects[counterRect].setFillColor(Color::Black);
			rects[counterRect].setOutlineColor(Color::White);
			rects[counterRect].setOutlineThickness(1.f);
			counterRect++;
		
		}
	}
	
	Player p = Player();
	Rays r = Rays(150, 100, 110, grid, X, Y);
	int keytime = 5;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent (event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}


		//Update
		p.update(keytime);

		r.update(p.getPosition(), p.getRotation());


		//clear previous frame
		window.clear(Color::White);

		//draw
		for (int i = 0; i<X*Y; i++) {
			window.draw(rects[i]);
		}
		p.drawPlayer(window);
		r.drawRays(window);

		//display new frame
		window.display();
	} 
	return 0;
}


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
		//std::cout << value << " ";
		std::cout << (int)i%(*Y) << " ";
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


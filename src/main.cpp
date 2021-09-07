/**
 * \file main.cpp
 * \brief main function
 * \date 07/09/2021
 * \author Aki Schmatzler
 */

#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Player.hpp"
#include "Rays.hpp"
#include "Grid.hpp"

using namespace sf;
#define MAX_ARR 100
#define SIZE_SQUARE 64


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
	

	Player p = Player(150, 100, 110, grid, X, Y);
	//Rays r = Rays(150, 100, 110, grid, X, Y);
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



		//clear previous frame
		window.clear(Color::White);

		//draw
		for (int i = 0; i<X*Y; i++) {
			window.draw(rects[i]);
		}
		p.drawPlayer(window);

		//display new frame
		window.display();
	} 
	return 0;
}
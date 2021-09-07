/**
 * \file Rays.cpp
 * \brief definition of functions for Rays class
 * \date 07/09/2021
 * \author Aki Schmatzler
 */

#include "Rays.hpp"

Rays::Rays(int _nbRays, int _maxDistance, int _viewAngle, int** _grid, int _X, int _Y) {
	nbRays = _nbRays;
	maxDistance = _maxDistance;
	viewAngle = _viewAngle;
	grid = _grid;
	X = _X;
	Y = _Y;
}

void Rays::drawRays(sf::RenderWindow &window) {
	for (int i = 0; i<nbRays; i++) {
		double radiAngle = ((double) (viewAngle/nbRays)*i - playerRotation)*PI/180; // converting degrees to radians

		if (radiAngle < 0) radiAngle += 2*PI;
		else if (radiAngle > 2*PI) radiAngle -= 2*PI;

		sf::Vertex line[] = {sf::Vertex(playerPosition), sf::Vertex(distanceToWall(radiAngle, window))};
    	line[0].color = sf::Color::Blue;
		line[1].color = sf::Color::Blue;
		window.draw(line, 2, sf::Lines);
	}
}


sf::Vector2f Rays::distanceToWall(double angle, sf::RenderWindow &window) {

	sf::Vector2f cH;

	//height and width (it's all squares!)
	int cellHeightWidth = window.getSize().x / X;
	double px = playerPosition.x;
	double py = playerPosition.y;
	int xTmp, yTmp;
	int xOffset, yOffset;


	//checking horizontal lines first

 	if (angle < PI) {		//facing up
		yTmp = std::floor(py/cellHeightWidth) * cellHeightWidth - 1; 
		yOffset = -cellHeightWidth;
	}

	else if (angle > PI){ 	//facing down
		yTmp = std::floor(py/cellHeightWidth) * cellHeightWidth + cellHeightWidth;
		yOffset = cellHeightWidth;
	}

	else yTmp = py;	//horizontal (if angle == PI)

	xOffset = -yOffset/tan(angle);

	if (angle != PI && angle != 0) xTmp = (int) px + (py-yTmp)/tan(angle);
	else if (angle == 0) {xTmp = window.getSize().x - 1;}
	else if (angle == PI) {xTmp = 0;}
	
 	for (int depth = 0; depth < 7; depth++) {
		 
		int xTab = std::floor(xTmp / cellHeightWidth);
		int yTab = std::floor(yTmp / cellHeightWidth);

		
	 	if (xTab >= 0 && yTab >= 0 && xTab < X && yTab < Y){
			if (grid[yTab][xTab] != 0){
				depth = 8; //there's a wall!
			} 
			else {
				xTmp += xOffset;
				yTmp += yOffset;
			}
		} 
	}

	cH.x = xTmp; cH.y = yTmp;

	if (angle > PI/2 && angle < 3*PI/2) {		//facing left
		xTmp = std::floor(px/cellHeightWidth) * cellHeightWidth - 1; 
		xOffset = -cellHeightWidth;
	}

	else if (angle < PI/2 || angle > 3*PI/2){ 	//facing right
		xTmp = std::floor(px/cellHeightWidth) * cellHeightWidth + cellHeightWidth;
		xOffset = cellHeightWidth;
	}

	else xTmp = px;	//horizontal (if angle == PI/2 or 3PI/2)

	yOffset = - xOffset * tan(angle);

	if (angle != PI && angle != 0) yTmp = (int) py + (px-xTmp) * tan(angle);
	else if (angle > 3*PI/2-0.01 && angle < 3*PI/2 + 0.01) {std::cout << "hihi\n"; yTmp = window.getSize().y - 1;}
	else if (angle > PI/2-0.01 && angle < PI/2 + 0.01) {yTmp = 0;}
	
 	for (int depth = 0; depth < 7; depth++) {
		 
		int xTab = std::floor(xTmp / cellHeightWidth);
		int yTab = std::floor(yTmp / cellHeightWidth);

		
	 	if (xTab >= 0 && yTab >= 0 && xTab < X && yTab < Y){

			if (grid[yTab][xTab] != 0){
				depth = 8; //there's a wall!
			} 
			else {
				xTmp += xOffset;
				yTmp += yOffset;
			}
		} 
	} 

	
	double distanceToHorizontal = sqrt((cH.x-px)*(cH.x-px) + (cH.y-py)*(cH.y-py));
	double distanceToVertical = sqrt((xTmp-px)*(xTmp-px) + (yTmp-py)*(yTmp-py));

	if (distanceToHorizontal < distanceToVertical) return cH;
	else return sf::Vector2f(xTmp, yTmp);
}

void Rays::update(sf::Vector2f position, float rotation) {
	playerPosition = position;
	playerRotation = rotation;
}
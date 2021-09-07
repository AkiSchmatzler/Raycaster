/**
 * \file Rays.hpp
 * \brief header for Rays class
 * This class is there to define behavior of the rays 
 * \date 07/09/2021
 * \author Aki Schmatzler
 */


#ifndef __RAYS_H
#define __RAYS_H

#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"

#define PI 3.1415926

class Rays {
public:
	Rays(int _nbRays, int _maxDistance, int _viewAngle, int** _grid, int _X, int _Y);
	Rays(){};
	void drawRays(sf::RenderWindow &window);
	void update(sf::Vector2f position, float rotation);
	//returns maxDistance if there's no wall in that direction
	sf::Vector2f distanceToWall(double angle, sf::RenderWindow &window);

private:
	int X;
	int Y;
	int** grid;
	int nbRays;
	int maxDistance;
	double viewAngle;
	float playerRotation;
	sf::Vector2f playerPosition;
};

#endif
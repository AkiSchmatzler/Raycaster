/**
 * \file Player.hpp
 * \brief header for Player class
 * \date 07/09/2021
 * \author Aki Schmatzler
 */


#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Rays.hpp"

class Player : public sf::RectangleShape {

public:

	Player(int _nbRays, int _maxDistance, int _viewAngle, int** _grid, int _X, int _Y);

	Player(){}
	
	void update(int &keyTime);

	void drawPlayer(sf::RenderWindow &window);

	sf::Vector2f getPosition() {return position;}

	float getRotation(){return rotation;}

private:
	Rays rays;
	sf::Vector2f position;
	float rotation;
	sf::RectangleShape player;
	void updatePosition(sf::Vector2f newPos);
	void updateRotation(float angle);
};

#endif
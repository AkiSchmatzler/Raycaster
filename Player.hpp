#ifndef __PLAYER_H
#define __PLAYER_H

#include <iostream>
#include "SFML/Graphics.hpp"

class Player : public sf::RectangleShape {

public:
	Player();

	void update(int &keyTime);

	void drawPlayer(sf::RenderWindow &window);

	sf::Vector2f getPosition() {return position;}

	float getRotation(){return rotation;}

private:
	sf::Vector2f position;
	float rotation;
	sf::RectangleShape player;
	void updatePosition(sf::Vector2f newPos);
	void updateRotation(float angle);
};

#endif
/**
 * \file Player.cpp
 * \brief definition of function on Player class
 * \date 07/09/2021
 * \author Aki Schmatzler
 */

#include "Player.hpp"

Player::Player(int _nbRays, int _maxDistance, int _viewAngle, int** _grid, int _X, int _Y) {
	rays = Rays(_nbRays, _maxDistance, _viewAngle,_grid, _X, _Y);
	player = RectangleShape(sf::Vector2f(15.f, 15.f));
	position = sf::Vector2f(100.f, 100.f);
	player.setOrigin(player.getSize().x/2, player.getSize().y/2);
	player.setPosition(position);
	player.setFillColor(sf::Color::Magenta);
}


void Player::drawPlayer(sf::RenderWindow &window) {
	window.draw(player);
	rays.drawRays(window);
}

void Player::update(int &keyTime) {
	if (keyTime < 5)
		keyTime++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		keyTime = 0;
		updatePosition(sf::Vector2f(0.f, -5.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		keyTime = 0;
		updatePosition(sf::Vector2f(-5.f, 0.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		keyTime = 0;
		updatePosition(sf::Vector2f(0.f, 5.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		keyTime = 0;
		updatePosition(sf::Vector2f(5.f, 0.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		keyTime = 0;
		updateRotation(5.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		keyTime = 0;
		updateRotation(-5.f);
	}
	rays.update(position, rotation);
}

void Player::updateRotation(float angle){
	rotation += angle;
	rotation = (int) rotation % 360;
	player.setRotation(rotation);
}

void Player::updatePosition(sf::Vector2f newPos) {
	position = position + newPos; 
	player.setPosition(position);
}
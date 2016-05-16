#pragma once
#include "main.h"

class PBall : public sf::CircleShape
{
public:
	PBall(int size = 20, int mass = 5);

	sf::Vector2f speed;
	float mass;
	sf::Vector2f velocity;
	sf::Vector2f center;

	void setSpeed(sf::Vector2f speedx);
	sf::Vector2f getSpeed();
	void setMass(int massx);
	float getMass();
	void setVelocity(sf::Vector2f velx);
	sf::Vector2f getVelocity();
	void setupCenter();
	void Center(sf::Vector2f centerx);
	sf::Vector2f getCenter();

	void updatePosition();
	void resolveEdges();

	~PBall();
};


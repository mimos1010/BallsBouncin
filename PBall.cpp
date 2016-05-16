#include "PBall.h"



PBall::PBall(int size, int mass)
{
	PBall::setRadius(size);
	PBall::setMass(mass);

}


PBall::~PBall()
{
}

//sets n gets
#pragma region SetsnGets
void PBall::setSpeed(sf::Vector2f speedx)
{
	PBall::speed = speedx;
}
sf::Vector2f PBall::getSpeed()
{
	return PBall::speed;
}
void PBall::setMass(int massx) 
{
	PBall::mass = massx;
}
float PBall::getMass()
{
	return PBall::mass;
}
void PBall::setVelocity(sf::Vector2f velx) 
{
	PBall::velocity = velx;
}
sf::Vector2f PBall::getVelocity() 
{
	return PBall::velocity;
}
void PBall::setupCenter() {
	sf::Vector2f centerxy(PBall::getPosition().x + PBall::getRadius(), PBall::getPosition().y + PBall::getRadius());
	PBall::center = centerxy;
}
void PBall::Center(sf::Vector2f centerx) {
	sf::Vector2f centerxy(PBall::getPosition().x + PBall::getRadius(), PBall::getPosition().y + PBall::getRadius());
	PBall::setPosition(centerxy);
}
sf::Vector2f PBall::getCenter() {
	return PBall::center;
}
#pragma endregion All the setting and getting of various variables


void PBall::updatePosition() 
{
	PBall::setPosition(PBall::getPosition().x + PBall::getVelocity().x, PBall::getPosition().y + PBall::getVelocity().y);
}

void PBall::resolveEdges() {
	if (PBall::center.x + PBall::getRadius() >= 800)
	{
		PBall::setPosition(PBall::getPosition().x - 2, PBall::getPosition().y);
		PBall::velocity.x *= -1;
	}
	if (PBall::center.x - PBall::getRadius() <= 0)
	{
		PBall::setPosition(PBall::getPosition().x + 2, PBall::getPosition().y);
		PBall::velocity.x *= -1;
	}
	if (PBall::center.y + PBall::getRadius() >= 640)
	{
		PBall::setPosition(PBall::getPosition().x, PBall::getPosition().y - 2);
		PBall::velocity.y *= -1;
	}
	if (PBall::center.y - PBall::getRadius() <= 0)
	{
		PBall::setPosition(PBall::getPosition().x, PBall::getPosition().y + 2);
		PBall::velocity.y *= -1;
	}
}


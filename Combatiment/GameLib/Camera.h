#pragma once
#ifndef INCLUDE_CAMERA
#define INCLUDE_CAMERA

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Camera : public sf::View
{
private:
	sf::Time time = sf::Time::Zero;
	/*sf::Time initialTime = sf::Time::Zero;
	float angle = 0;*/
	float intensity = 0;
	sf::Vector2f lastCenter;
	sf::Vector2f newCenter;

public:
	sf::RenderWindow* window;
	void shake(float intensity, sf::Time time);
	void update(sf::Time dt);
};

#endif // !INCLUDE_CAMERA


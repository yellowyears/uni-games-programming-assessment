/************************************************Task A-iv*************************************************************
All the fields and methods of the Trail class are currently declared public.
Refactor the class to use the most appropriate access controls (public, private, or protected) for all members.
************************************************************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Trail
{
public:
	Trail(const sf::Vector2f& pos, float radius)
		: remainingLife(0.3f), radius(radius), position(pos)
	{
		createShape();
	}

	void update(float dt)
	{
		remainingLife -= dt;
		sf::Color color = circle.getFillColor();
		if (color.a > 0)
		{
			color.a = static_cast<int>(std::max(0.f, (remainingLife / 0.3f) * 180.f));
			circle.setFillColor(color);
		}
	}

	bool dead() const
	{
		return remainingLife <= 0;
	}

	void draw(sf::RenderWindow& window) const
	{
		window.draw(circle);
	}

	~Trail()
	{
		std::cout << "Dead traill destroyed!\n";
	}
private:
	sf::CircleShape circle;
	float remainingLife, radius;
	sf::Vector2f position;

	void createShape()
	{
		circle.setRadius(radius);
		circle.setOrigin(sf::Vector2f(radius, radius));
		circle.setPosition(position);
		circle.setFillColor(sf::Color(255, 255, 0, 180));
	}
};
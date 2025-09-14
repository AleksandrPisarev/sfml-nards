#pragma once
#include <SFML/Graphics.hpp>
class Hint
{
	sf::CircleShape circle;
public:
	Hint();
	void setPosition(sf::Vector2f position);
	void render(sf::RenderWindow& window);
	sf::Vector2f getPosition();
};


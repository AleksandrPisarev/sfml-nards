#pragma once
#include <SFML/Graphics.hpp>

class Dice
{
	sf::RectangleShape rectangle;
	std::vector<sf::CircleShape> circles;
	bool active = true;
public:
	explicit Dice(int number);
	void render(sf::RenderWindow& window);
	void setPosition(int offset);
	void setPositionForComp(int offset);
	int getCircles();
	bool get—ondition();
	void noMove();
	void off();
};


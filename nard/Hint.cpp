#include "Hint.h"
Hint::Hint() {
	circle.setRadius(13);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Color(0, 255, 0, 150));
}

void Hint::setPosition(sf::Vector2f position) {
	circle.setPosition(position);
}

void Hint::render(sf::RenderWindow& window) {
	window.draw(circle);
}

sf::Vector2f Hint::getPosition()
{
	return circle.getPosition();
}
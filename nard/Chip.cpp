#include "Chip.h"
Chip::Chip(sf::Color color)
{
	shape.setRadius(13);
	shape.setOrigin(shape.getRadius(), shape.getRadius()); // перемещает точку координат с левого верхнего угла в центр круга
	shape.setFillColor(color);
}

void Chip::setPosition(sf::Vector2f position)
{
	shape.setPosition(position);
}

void Chip::render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Chip::move(int position, int count)
{
	if (position >= 0 && position <= 11) {
		shape.setPosition(sf::Vector2f(fieldCoord[position].x, fieldCoord[position].y - count * 27.f));
	}
	else {
		shape.setPosition(sf::Vector2f(fieldCoord[position].x, fieldCoord[position].y + count * 27.f));
	}
}

sf::Vector2f Chip::getPosition()
{
	return shape.getPosition();
}

sf::Color Chip::getColor()
{
	return shape.getFillColor();
}
//делает контур зеленым когда на фишку кликнули мышкой
void Chip::on()
{
	shape.setOutlineThickness(-2);
	shape.setOutlineColor(sf::Color::Green);
}
// возвращает фишке прежний цвет
void Chip::off()
{
	shape.setOutlineThickness(0);
}
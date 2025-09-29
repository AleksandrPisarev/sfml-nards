#include "Dice.h"
Dice::Dice(int number)
{
	rectangle.setSize(sf::Vector2f(30, 30));
	rectangle.setFillColor(sf::Color(255, 255, 255));
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	sf::CircleShape circle;
	circle.setRadius(3);
	circle.setFillColor(sf::Color(0, 0, 0));
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	for (int i = 0; i < number; i++) {
		circles.push_back(circle);
	}
}

void Dice::render(sf::RenderWindow& window)
{
	window.draw(rectangle);
	for (int i = 0; i < circles.size(); i++) {
		window.draw(circles[i]);
	}
}

void Dice::setPosition(int offset)
{
	rectangle.setPosition(200 + offset, 400);
	switch (circles.size()) {
	case 1:
		circles[0].setPosition(200 + offset, 400);
		break;
	case 2:
		for (int i = 0, shift = 0; i < circles.size(); ++i, shift += 20) {
			circles[i].setPosition(190 + shift + offset, 390 + shift);
		}
		break;
	case 3:
		for (int i = 0, shift = 0; i < circles.size(); ++i, shift += 10) {
			circles[i].setPosition(190 + shift + offset, 390 + shift);
		}
		break;
	case 4:
		for (int i = 0, shift = 0; i < 2; ++i, shift += 20) {
			circles[i].setPosition(190 + shift + offset, 390);
		}
		for (int i = 2, shift = 0; i < circles.size(); ++i, shift += 20) {
			circles[i].setPosition(190 + shift + offset, 410);
		}
		break;
	case 5:
		for (int i = 0, shift = 0; i < 2; ++i, shift += 20) {
			circles[i].setPosition(190 + shift + offset, 390);
		}
		for (int i = 2, shift = 0; i < 4; ++i, shift += 20) {
			circles[i].setPosition(190 + shift + offset, 410);
		}
		circles[4].setPosition(200 + offset, 400);
		break;
	case 6:
		for (int i = 0, shift = 0; i < 3; ++i, shift += 10) {
			circles[i].setPosition(190 + shift + offset, 390);
		}
		for (int i = 3, shift = 0; i < circles.size(); ++i, shift += 10) {
			circles[i].setPosition(190 + shift + offset, 410);
		}
		break;
	}
}

void Dice::setPositionForComp(int offset)
{
	rectangle.setPosition(500 + offset, 400);
	switch (circles.size()) {
	case 1:
		circles[0].setPosition(500 + offset, 400);
		break;
	case 2:
		for (int i = 0, shift = 0; i < circles.size(); ++i, shift += 20) {
			circles[i].setPosition(490 + shift + offset, 390 + shift);
		}
		break;
	case 3:
		for (int i = 0, shift = 0; i < circles.size(); ++i, shift += 10) {
			circles[i].setPosition(490 + shift + offset, 390 + shift);
		}
		break;
	case 4:
		for (int i = 0, shift = 0; i < 2; ++i, shift += 20) {
			circles[i].setPosition(490 + shift + offset, 390);
		}
		for (int i = 2, shift = 0; i < circles.size(); ++i, shift += 20) {
			circles[i].setPosition(490 + shift + offset, 410);
		}
		break;
	case 5:
		for (int i = 0, shift = 0; i < 2; ++i, shift += 20) {
			circles[i].setPosition(490 + shift + offset, 390);
		}
		for (int i = 2, shift = 0; i < 4; ++i, shift += 20) {
			circles[i].setPosition(490 + shift + offset, 410);
		}
		circles[4].setPosition(500 + offset, 400);
		break;
	case 6:
		for (int i = 0, shift = 0; i < 3; ++i, shift += 10) {
			circles[i].setPosition(490 + shift + offset, 390);
		}
		for (int i = 3, shift = 0; i < circles.size(); ++i, shift += 10) {
			circles[i].setPosition(490 + shift + offset, 410);
		}
		break;
	}
}

int Dice::getCircles()
{
	return circles.size();
}

bool Dice::getÑondition()
{
	return active;
}

void Dice::noMove()
{
	rectangle.setFillColor(sf::Color(255, 0, 0, 128));
}

void Dice::off()
{
	active = false;
	rectangle.setFillColor(sf::Color(255, 255, 255, 128));
	for (int i = 0; i < circles.size(); ++i) {
		circles[i].setFillColor(sf::Color(0, 0, 0, 128));
	}
}
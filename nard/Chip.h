#pragma once
#include <SFML/Graphics.hpp>
class Chip
{
	friend class Game;
	sf::CircleShape shape;
	static sf::Vector2f fieldCoord[24];   // сделал параметр статическим поскольку он не меняется и общий для всех объектов
public:
	Chip(sf::Color color);
	void setPosition(sf::Vector2f position);
	void render(sf::RenderWindow& window);
	void move(int position, int count);
	sf::Vector2f getPosition();
	sf::Color getColor();
	void on();                     //делает контур зеленым когда на фишку кликнули мышкой
	void off();                    // возвращает фишке прежний цвет
};
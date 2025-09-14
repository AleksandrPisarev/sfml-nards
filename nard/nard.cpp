#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

sf::Vector2f Chip::fieldCoord[24] = {
		 sf::Vector2f(121.f,676.f), sf::Vector2f(166.f,676.f), sf::Vector2f(211.f,676.f), sf::Vector2f(256.f,676.f),
		 sf::Vector2f(301.f,676.f), sf::Vector2f(346.f,676.f), sf::Vector2f(452.f,676.f), sf::Vector2f(497.f,676.f),
		 sf::Vector2f(542.f,676.f), sf::Vector2f(587.f,676.f), sf::Vector2f(632.f,676.f), sf::Vector2f(677.f,676.f),

		 sf::Vector2f(677.f, 127.f), sf::Vector2f(632.f, 127.f), sf::Vector2f(587.f, 127.f), sf::Vector2f(542.f, 127.f),
		 sf::Vector2f(497.f, 127.f), sf::Vector2f(452.f, 127.f), sf::Vector2f(346.f, 127.f), sf::Vector2f(301.f, 127.f),
		 sf::Vector2f(256.f, 127.f), sf::Vector2f(211.f, 127.f), sf::Vector2f(166.f, 127.f), sf::Vector2f(121.f, 127.f),
};

int main()
{
	srand(time(0));
	Game game;
	game.run();
}
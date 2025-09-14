#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include "Chip.h"
#include "Dice.h"
#include "Hint.h"
class Game
{
	sf::RenderWindow window;
	sf::Texture bgTextur, buttonTextur;
	sf::Sprite bgSprite, buttonSprite;
	std::vector<Chip> field[24];
	std::vector<Dice> dice;           // хранит массив кубиков
	std::vector<Hint> hints;          // массив кружков подсказывающих возможные ходы
	bool playingSide = true;          // переменна€ определ€юща€ кто совершает ход игрок или компьютер
	sf::Event event;
public:
	Game();
	void run();
private:
	void processEvent();
	void update();
	void render();
	void startPosition();
	bool movingChips();                         // функци€ перемещение фишек
	void movingComp();                          // функци€ перемещение фишек компьютера
	void rollOfDice();                          // функци€ бросок кубиков
	bool playerToGo();                          // функци€ ход игрока
	bool computerToGo();                        // функци€ ход компьютера
};


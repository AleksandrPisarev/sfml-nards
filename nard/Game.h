#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<vector>
#include<Windows.h>
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
	bool rollDice = false;            // переменна€ показывающа€ брошены ли кубики нужна дл€ услови€ в рендере дл€ изменеи€ playingSide
	int endMove = 0;                  // переменна€ определ€юща€ конец хода
	sf::Event event;
public:
	Game();
	void run();
private:
	void processEvent();
	void update();
	void render();
	void startPosition();
	void movingChips();                                            // функци€ перемещение фишек
	void movingComp();                                             // функци€ перемещение фишек компьютера
	void rollOfDice();                                             // функци€ бросок кубиков
	void playerToGo();                                             // функци€ ход игрока
	void computerToGo();                                           // функци€ ход компьютера
	void changingPositionsChips(int, int);                         // функци€ изменение позиций фишек создана дл€ уменьшени€ кода в услови€х хода компьютера
	bool possibilityMoveComp(bool, std::vector<Dice>);             // проверка возможности хода компьютера
};


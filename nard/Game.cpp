#include "Game.h"
Game::Game() : window(sf::VideoMode(800, 800), "Nard")
{
    if (!bgTextur.loadFromFile("board.jpg")) {
        std::cout << "file not loaded";
    }
    bgSprite.setTexture(bgTextur);
    bgSprite.setPosition(sf::Vector2f(40.f, 40.f));
    startPosition();
    if (!buttonTextur.loadFromFile("dice.png")) {
        std::cout << "file not loaded";
    }
    buttonSprite.setTexture(buttonTextur);
    buttonSprite.setPosition(sf::Vector2f(350.f, 375.f));
}

void Game::run()
{
    while (window.isOpen())
    {
         processEvent();
         update();
         render();
    }
}

void Game::processEvent()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (playingSide == true) {
                    playingSide = playerToGo();
                }
            }
        }
        else  buttonSprite.setColor(sf::Color(255, 255, 255, 255));
    }
}

void Game::update()
{
    if (playingSide == false) {
        playingSide = computerToGo();
    }
}

void Game::render()
{
    window.clear(sf::Color(0,0,102));
    window.draw(bgSprite);
    window.draw(buttonSprite);
    for (int i = 0; i < 24; i++) {
        for (auto el : field[i]) {
            el.render(window);
        }
    }
    for (int i = 0; i < dice.size(); i++) {
        dice[i].render(window);
    }
    for (int i = 0; i < hints.size(); i++) {
        hints[i].render(window);
    }
    window.display();
}

void Game::startPosition()
{
    for (int i = 0; i < 15; i++) {
        Chip chip(sf::Color::Red);
        chip.move(0, field[0].size());
        field[0].push_back(chip);
    }

    for (int i = 0; i < 15; i++) {
        Chip chip(sf::Color::Black);
        chip.move(12, field[12].size());
        field[12].push_back(chip);
    }
}
// функция перемещение фишек
bool Game::movingChips()
{
    static int activeChip = -1;              // переменная для определения какая фишка активная (какая фишка будет ходить)
    double distance;
    ////////// проверяет клик мыши на попадание на фишку //////////
    // activChip переменная которая определяет кликнули на фишку или нет если на фишку кликнули она принимает значение индекса массива Field
    // изначально activeChip = -1
    if (activeChip < 0) {
        for (int i = 0; i < 24; i++) {
            if ((field[i].size() != 0) && (field[i][field[i].size() - 1].getColor() == sf::Color::Red)) {
                // переменная которая определяет расстояние от клика мышки до центра фишки если расстояние меньше радиуса фишки
                // значит клик попал на фишку и она стала активной
                distance = sqrt(pow((event.mouseButton.x - field[i][field[i].size() - 1].getPosition().x), 2) + pow((event.mouseButton.y - field[i][field[i].size() - 1].getPosition().y), 2));
                if (distance <= 13) {
                    activeChip = i;
                    field[activeChip][field[activeChip].size() - 1].on();
                    break;
                }
            }
        }
        // после определения активной фишки  создание подсказок в виде зеленых кружков
        if ((activeChip >= 0) && (dice.size() == 2) && (dice[0].getCircles() != dice[1].getCircles())) {
            bool flag = false; // устанавливается чтобы проверить есть ли возможность хода по первому или второму кубику если да тогда возможно есть возможность походить сразу по двум
            //кубикам
            for (int i = 0; i < dice.size(); ++i) {
                if (field[activeChip + dice[i].getCircles()].size() == 0 || field[activeChip + dice[i].getCircles()][0].getColor() == sf::Color::Red) {
                    flag = true;
                    Hint hint;
                    hint.setPosition(Chip::fieldCoord[activeChip + dice[i].getCircles()]);
                    hints.push_back(hint);
                }
            }
            if ((flag == true) && (field[activeChip + dice[0].getCircles() + dice[1].getCircles()].size() == 0 || field[activeChip + dice[0].getCircles() + dice[1].getCircles()][0].getColor() == sf::Color::Red)) {
                Hint hint;
                hint.setPosition(Chip::fieldCoord[activeChip + dice[0].getCircles() + dice[1].getCircles()]);
                hints.push_back(hint);
            }
        }
        else if ((activeChip >= 0) && (dice.size() == 4 || dice.size() == 3 || ((dice.size() == 2) && (dice[0].getCircles() == dice[1].getCircles())))) {
            int count = 1;
            for (int i = 0; i < dice.size(); ++i) {
                if (field[activeChip + (dice[i].getCircles() * count)].size() == 0 || field[activeChip + (dice[i].getCircles() * count)][0].getColor() == sf::Color::Red) {
                    Hint hint;
                    hint.setPosition(Chip::fieldCoord[activeChip + dice[i].getCircles() * count]);
                    hints.push_back(hint);
                    ++count;
                }
                else break;
            }
        }
        else if ((activeChip >= 0) && (dice.size() == 1) && (field[activeChip + dice[0].getCircles()].size() == 0 || field[activeChip + dice[0].getCircles()][0].getColor() == sf::Color::Red)) {
            Hint hint;
            hint.setPosition(Chip::fieldCoord[activeChip + dice[0].getCircles()]);
            hints.push_back(hint);
        }
    }
    ////////// проверяет клик мыши на то место куда необходимо переставить фишку //////////
    else if (activeChip >= 0) {
        int index = -1; //переменная координата x для перемещения фишки
        for (int i = 0; i < hints.size(); ++i) {
            distance = sqrt(pow(event.mouseButton.x - hints[i].getPosition().x, 2) + pow(event.mouseButton.y - hints[i].getPosition().y, 2));
            if (distance <= 13) {
                for (int j = 0; j < 24; ++j) {
                    if (hints[i].getPosition() == Chip::fieldCoord[j]) {
                        index = j;
                        break;
                    }
                }
                // изменение координаты фишки куда ее переставили и изменение положения в массиве
                field[activeChip][field[activeChip].size() - 1].move(index, field[index].size());
                field[index].push_back(field[activeChip][field[activeChip].size() - 1]);
                field[activeChip].pop_back();
                int indexDifference = index - activeChip; // переменная разница координат откуда-куда ходили необходима для установления какой кубик использовался для хода
                bool erase = false;
                // удаление кубиков по которым был сделан ход
                for (int j = 0; j < dice.size(); ++j) {
                    if (dice[j].getCircles() == indexDifference) {
                        dice.erase(dice.begin() + j);
                        erase = true;
                        break;
                    }
                }
                if (erase == false) {
                    if ((dice[0].getCircles() + dice[1].getCircles()) == indexDifference) {
                        dice.pop_back();
                        dice.pop_back();
                    }
                    else if ((dice[0].getCircles() * 3) == indexDifference) {
                        dice.pop_back();
                        dice.pop_back();
                        dice.pop_back();
                    }
                    else if ((dice[0].getCircles() * 4) == indexDifference) {
                        dice.clear();
                    }
                }
            }
        }
        if (index == -1) field[activeChip][field[activeChip].size() - 1].off();
        else field[index][field[index].size() - 1].off();
        activeChip = -1;
        hints.clear();
    }
    if (dice.size() == 0) return 0;
    else return 1;
}
// функция бросок кубиков
void Game::rollOfDice()
{
    int random[2];
    for (int i = 0; i < 2; ++i) {
        random[i] = rand() % (6 - 1 + 1) + 1;
    }
    if (random[0] == random[1]) {
        for (int i = 0; i < 4; i++) {
            Dice cube(random[0]);
            if (playingSide == true) cube.setPosition(i * 40);
            else cube.setPositionForComp(i * 40);
            dice.push_back(cube);
        }
    }
    else {
        for (int i = 0; i < 2; i++) {
            Dice cube(random[i]);
            if (playingSide == true) cube.setPosition(i * 40);
            else cube.setPositionForComp(i * 40);
            dice.push_back(cube);
        }
    }
}

// функция ход игрока
bool Game::playerToGo()
{
    static bool diceSize = false;
    if (diceSize == false) dice.clear();
    if ((dice.size() == 0) && event.mouseButton.x >= buttonSprite.getPosition().x &&
        event.mouseButton.x <= buttonSprite.getPosition().x + 100 &&
        event.mouseButton.y >= buttonSprite.getPosition().y &&
        event.mouseButton.y <= buttonSprite.getPosition().y + 51) {
        rollOfDice();
        diceSize = true;
        buttonSprite.setColor(sf::Color(255, 255, 255, 128));
        return 1;
    }
    else if (dice.size() != 0) {
        diceSize = movingChips();
        if (diceSize == 0) return 0;
        else return 1;
    }
    else return 1;
}

// функция перемещение фишек компьютера
void Game::movingComp()
{
    std::vector<Dice> tempDice = dice; //копия массива кубиков
    if (tempDice[0].getCircles() > tempDice[1].getCircles()) {
        Dice temp = tempDice[0];
        tempDice[0] = tempDice[1];
        tempDice[1] = temp;
    }
    bool one_move = false;             // переменная для хода из головы только один раз
    while (tempDice.size() != 0) {
        if (field[12].size() != 0) {
            int countBlack = 0;         // колмчество полей занятых черными
            for (int i = 13; i < 19; ++i) {
                if (field[i].size() != 0) ++countBlack;
            }
            if (countBlack >= 4) {

            }
            else {
                if (one_move == false) {
                    if (field[12 + tempDice[0].getCircles()].size() == 0) {
                        field[12][field[12].size() - 1].move((12 + tempDice[0].getCircles()), field[12 + tempDice[0].getCircles()].size());
                        field[12 + tempDice[0].getCircles()].push_back(field[12][field[12].size() - 1]);
                        field[12].pop_back();
                        tempDice.erase(tempDice.begin());
                        one_move = true;
                    }
                    else if (field[12 + tempDice[1].getCircles()].size() == 0) {
                        field[12][field[12].size() - 1].move((12 + tempDice[1].getCircles()), field[12 + tempDice[1].getCircles()].size());
                        field[12 + tempDice[1].getCircles()].push_back(field[12][field[12].size() - 1]);
                        field[12].pop_back();
                        tempDice.erase(tempDice.begin() + 1);
                        one_move = true;
                    }
                    else if (field[12 + tempDice[0].getCircles() + tempDice[1].getCircles()].size() == 0) {
                        field[12][field[12].size() - 1].move((12 + tempDice[0].getCircles() + tempDice[1].getCircles()), field[12 + tempDice[0].getCircles() + tempDice[1].getCircles()].size());
                        field[12 + tempDice[0].getCircles() + tempDice[1].getCircles()].push_back(field[12][field[12].size() - 1]);
                        field[12].pop_back();
                        tempDice.erase(tempDice.begin());
                        one_move = true;
                    }
                }
                else if (one_move == true) {
                    for (int i = 22; i >= 19; --i) {
                        if (field[i].size() >= 2 && field[i][0].getColor() == sf::Color::Black) {
                            for (int j = 0; j < tempDice.size(); ++j) {
                                if (field[i + tempDice[j].getCircles()].size() == 0) {

                                }
                            }
                        }
                    }

                }
            }
        }
    }
}

// функция ход компьютера
bool Game::computerToGo()
{
    rollOfDice();
   /* movingComp();*/
    return 1;
}
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

        if (playingSide == true && event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {
                playerToGo();
            }
        }
        else  buttonSprite.setColor(sf::Color(255, 255, 255, 255));
    }
}

void Game::update()
{
    if (playingSide == false) {
        computerToGo();
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
    if (rollDice == true && endMove == 0) {
        if (playingSide == true) {
            playingSide = false;
            rollDice = false;
        }
        else {
            playingSide = true;
            rollDice = false;
        }
    }
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
void Game::movingChips()
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
        if ((activeChip >= 0) && (endMove == 2) && (dice[0].getCircles() != dice[1].getCircles())) {
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
        else if ((activeChip >= 0) && (endMove == 4 || endMove == 3 || endMove == 2)) {
            int count = 1;
            for (int i = 0; i < dice.size(); ++i) {
                if (dice[i].getСondition() == false) continue;
                if (field[activeChip + (dice[i].getCircles() * count)].size() == 0 || field[activeChip + (dice[i].getCircles() * count)][0].getColor() == sf::Color::Red) {
                    Hint hint;
                    hint.setPosition(Chip::fieldCoord[activeChip + dice[i].getCircles() * count]);
                    hints.push_back(hint);
                    ++count;
                }
                else break;
            }
        }
        else if (activeChip >= 0 && endMove == 1) {
            for (int i = 0; i < dice.size(); ++i) {
                if (dice[i].getСondition() == true && (field[activeChip + dice[i].getCircles()].size() == 0 || field[activeChip + dice[i].getCircles()][0].getColor() == sf::Color::Red)) {
                    Hint hint;
                    hint.setPosition(Chip::fieldCoord[activeChip + dice[i].getCircles()]);
                    hints.push_back(hint);
                }
            }
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
                // выключение кубиков по которым был сделан ход
                int count = 0; // счетчик сколько кубиков необходимо выключить
                if (dice[0].getCircles() == indexDifference || dice[1].getCircles() == indexDifference) {
                    for (int j = 0; j < dice.size(); ++j) {
                        if (dice[j].getСondition() == true && dice[j].getCircles() == indexDifference && count < 1) {
                            dice[j].off();
                            ++count;
                        }
                    }
                    --endMove;
                }
                else if (dice[0].getCircles() + dice[1].getCircles() == indexDifference) {
                    for (int j = 0; j < dice.size(); ++j) {
                        if (dice[j].getСondition() == true && count < 2) {
                            dice[j].off();
                            ++count;
                        }
                    }
                    endMove -= 2;
                }
                else if ((dice[0].getCircles() * 3) == indexDifference) {
                    for (int j = 0; j < dice.size(); ++j) {
                        if (dice[j].getСondition() == true && count < 3) {
                            dice[j].off();
                            ++count;
                        }
                    }
                    endMove -= 3;
                }
                else if ((dice[0].getCircles() * 4) == indexDifference) {
                    endMove = 0;
                }
            }
        }
        if (index == -1) field[activeChip][field[activeChip].size() - 1].off();
        else field[index][field[index].size() - 1].off();
        activeChip = -1;
        hints.clear();
    }
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
void Game::playerToGo()
{
    if (endMove == 0 && event.mouseButton.x >= buttonSprite.getPosition().x &&
        event.mouseButton.x <= buttonSprite.getPosition().x + 100 &&
        event.mouseButton.y >= buttonSprite.getPosition().y &&
        event.mouseButton.y <= buttonSprite.getPosition().y + 51) {
        dice.clear();
        rollOfDice();
        endMove = dice.size();
        rollDice = true;
        buttonSprite.setColor(sf::Color(255, 255, 255, 128));
    }
    else if (endMove != 0) {
        movingChips();
    }
}

// функция перемещение фишек компьютера
void Game::movingComp()
{
    static bool firstMove = false;             // переменная первый ход
    static bool moveFromHead = false;          // переменная ход с головы
    if (firstMove == false) {
        if (dice[0].getCircles() != dice[1].getCircles()) {
            if (field[12 + dice[0].getCircles() + dice[1].getCircles()].size() == 0) {
                changingPositionsChips(12, dice[0].getCircles() + dice[1].getCircles());
                endMove = 0;
                firstMove = true;
            }
            else {
                if (dice[0].getCircles() > dice[1].getCircles()) {
                    changingPositionsChips(12, dice[0].getCircles());
                    dice[1].noMove();
                }
                else {
                    changingPositionsChips(12, dice[1].getCircles());
                    dice[0].noMove();
                }
                endMove = 0;
                firstMove = true;
            }
        }
        else {
            switch (dice[0].getCircles()) {
            case 1:
                changingPositionsChips(12, dice[0].getCircles() * 4);
                endMove = 0;
                firstMove = true;
                break;
            case 2:
                if (field[12 + (dice[0].getCircles() * 4)].size() == 0) {
                    changingPositionsChips(12, dice[0].getCircles() * 4);
                }
                else {
                    changingPositionsChips(12, dice[0].getCircles() * 3);
                    dice[3].noMove();
                }
                endMove = 0;
                firstMove = true;
                break;
            case 3:
                changingPositionsChips(12, dice[0].getCircles() * 3);
                changingPositionsChips(12, dice[0].getCircles());
                endMove = 0;
                firstMove = true;
                break;
            case 4:
                if (field[12 + (dice[0].getCircles() * 2)].size() == 0) {
                    changingPositionsChips(12, dice[0].getCircles() * 2);
                    changingPositionsChips(12, dice[0].getCircles() * 2);
                }
                else {
                    changingPositionsChips(12, dice[0].getCircles());
                    changingPositionsChips(12, dice[0].getCircles());
                    dice[2].noMove();
                    dice[3].noMove();
                }
                endMove = 0;
                firstMove = true;
                break;
            case 5:
                changingPositionsChips(12, dice[0].getCircles() * 2);
                if (field[3].size() == 0) {
                    changingPositionsChips(22, dice[0].getCircles());
                    if (field[8].size() == 0) {
                        changingPositionsChips(3, dice[0].getCircles());
                    }
                    else dice[3].noMove();
                }
                else {
                    dice[2].noMove();
                    dice[3].noMove();
                }
                endMove = 0;
                firstMove = true;
                break;
            case 6:
                changingPositionsChips(12, dice[0].getCircles());
                changingPositionsChips(12, dice[0].getCircles());
                dice[2].noMove();
                dice[3].noMove();
                endMove = 0;
                firstMove = true;
                break;
            }
        }
    }
    else if (firstMove == true) {
        bool possibilityMove;
        possibilityMove = possibilityMoveComp(moveFromHead, dice);
        if (possibilityMove == true) {
            if (field[12].size() != 0) {

            }
            else if (field[12].size() == 0) {

            }
        }
        else if (possibilityMove == false) {
            for (int i = 0; i < dice.size(); ++i) {
                dice[i].noMove();
            }
            endMove = 0;
        }
    }
    if (endMove == 0) moveFromHead = false;
}

// функция ход компьютера
void Game::computerToGo()
{
    if (endMove == 0) {
        dice.clear();
        rollOfDice();
        endMove = dice.size();
        rollDice = true;
    }
    else if (endMove != 0) {
        movingComp();
        Sleep(1000);
    }
}

// функция изменение позиций фишек создана для уменьшения кода в условиях хода компьютера
void Game::changingPositionsChips(int position, int dice)
{
    if ((position + dice) <= 23) {
        field[position][field[position].size() - 1].move((position + dice), field[position + dice].size());
        field[position + dice].push_back(field[position][field[position].size() - 1]);
        field[position].pop_back();
    }
    else {
        int index = (position + dice) - 24;
        field[position][field[position].size() - 1].move(index, field[index].size());
        field[index].push_back(field[position][field[position].size() - 1]);
        field[position].pop_back();
    }
}

// проверка возможности хода компьютера
bool Game::possibilityMoveComp(bool moveFromHead, std::vector<Dice> dice)
{
    int index;              // переменная определяющая с какой позиции будет анализироваться возможность хода
    if (moveFromHead == false) index = 12;
    else index = 13;
    std::vector<int> fromBlack; // массив индексов где находятся черные фишки
    for (int i = index; i < 24; ++i) {
        if (field[i].size() != 0 && field[i][0].getColor() == sf::Color::Black) {
            fromBlack.push_back(i);
        }
    }
    for (int i = 0; i < fromBlack.size(); ++i) {
        for (int j = 0; j < dice.size(); ++j) {
            int position = fromBlack[i] + dice[j].getCircles();
            if (position > 23) position = (fromBlack[i] + dice[j].getCircles()) - 24;
            if (field[position].size() == 0 || (field[position].size() != 0 && field[position][0].getColor() == sf::Color::Black)) return 1;
        }
    }
    fromBlack.clear();
    for (int i = 0; i < 12; ++i) {
        if (field[i].size() != 0 && field[i][0].getColor() == sf::Color::Black) {
            fromBlack.push_back(i);
        }
    }
    for (int i = 0; i < fromBlack.size(); ++i) {
        for (int j = 0; j < dice.size(); ++j) {
            int position = fromBlack[i] + dice[j].getCircles();
            if (position <= 11) {
                if (field[position].size() == 0 || (field[position].size() != 0 && field[position][0].getColor() == sf::Color::Black)) return 1;
            }
        }
    }
    return 0;
}
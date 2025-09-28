#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <fstream>
#include <stdio.h>
#include "Board.h"

void Board::draw(sf::RenderWindow* window) {
    for (auto& tile : tiles) {
        for (unsigned int j = 0; j < 16; j++) {
            tile[j]->draw(window, debugMode);
        }
    }

    resetButton->setPosition(368, 512);
    if (gameLost) {
        resetButton->setTexture(*faceLose);
    } else if (gameWon) {
        resetButton->setTexture(*faceWin);
    } else {
        resetButton->setTexture(*faceHappy);
    }
    window->draw(*resetButton);

    debugSprite->setTexture(*debugTexture);
    debugSprite->setPosition(496, 512);
    window->draw(*debugSprite);

    testSprite1->setTexture(*testTexture1);
    testSprite1->setPosition(560, 512);
    window->draw(*testSprite1);

    testSprite2->setTexture(*testTexture2);
    testSprite2->setPosition(624, 512);
    window->draw(*testSprite2);

    int display = numMines - numFlagged;
    if (display < 0) display = 0;
    int first = display / 10;
    int second = display % 10;

    digit1->setTexture(*textures[first]);
    digit1->setPosition(0, 512);
    window->draw(*digit1);
    digit2->setTexture(*textures[second]);
    digit2->setPosition(22, 512);
    window->draw(*digit2);
}

Tile* Board::getTile(int x, int y) {
    return tiles[x][y];
}

void Board::click(int x, int y, bool left) {
    if (y < 512 && left) {
        int xPos = x / 32;
        int yPos = y / 32;
        clickTile(xPos, yPos);
        checkWon();
    } else if (y < 512 && !left) {
        int xPos = x / 32;
        int yPos = y / 32;
        Tile* tile = tiles[xPos][yPos];
        if (tile->getClicked() || gameWon || gameLost) { return; }
        tile->flag();
        if (tile->getFlagged()) { numFlagged++; }
        else numFlagged--;
        checkWon();
    } else if (x >= 368 && x <= 432 && y >= 512 && y <= 576 && left) {
        reset();
        std::map<int, int> minemap = generateRandomVector();
        generateMines(minemap);
        calculateAdjacent();
    } else if (x >= 496 && x <= 560 && y >= 512 && y <= 576 && left) {
        debugMode = !debugMode;
    } else if (x >= 560 && x <= 624 && y >= 512 && y < 576 && left) {
        reset();
        std::map<int, int> minemap = loadMinesFromFile("boards/testboard.brd");
        generateMines(minemap);
        calculateAdjacent();
    } else if (x >= 624 && x <= 688 && y >= 512 && y < 576 && left) {
        reset();
        std::map<int, int> minemap = loadMinesFromFile("boards/testboard2.brd");
        generateMines(minemap);
        calculateAdjacent();
    }
}

void Board::clickTile(int xPos, int yPos) {
    Tile* tile = tiles[xPos][yPos];

    if (tile->getClicked() || gameWon || gameLost || tile->getFlagged()) {
        return;
    }

    tile->click();
    numClicked++;
    if (tile->getMine()) {
        end();
    }

    int adjacentMines = tiles[xPos][yPos]->getNumAdjacentMines();
    if (adjacentMines == 0) {
        if (xPos > 0) {
            clickTile(xPos - 1, yPos);
        }
        if (xPos < 24) {
            clickTile(xPos + 1, yPos);
        }
        if (yPos > 0) {
            clickTile(xPos, yPos - 1);
        }
        if (yPos < 15) {
            clickTile(xPos, yPos + 1);
        }
        if (xPos > 0 && yPos > 0) {
            clickTile(xPos - 1, yPos - 1);
        }
        if (xPos > 0 && yPos < 15) {
            clickTile(xPos - 1, yPos + 1);
        }
        if (xPos < 24 && yPos > 0) {
            clickTile(xPos + 1, yPos - 1);
        }
        if (xPos < 24 && yPos < 15) {
            clickTile(xPos + 1, yPos + 1);
        }
    }
}

void Board::checkWon() {
    if (numFlagged == numMines && numClicked + numFlagged == 400) {
        gameWon = true;
    }
}

void Board::end() {
    gameLost = true;
}

Board::Board() {

    srand(time(NULL));

    faceHappy = new sf::Texture;
    faceLose = new sf::Texture;
    faceWin = new sf::Texture;
    resetButton = new sf::Sprite;

    faceHappy->loadFromFile("images/face_happy.png");
    faceLose->loadFromFile("images/face_lose.png");
    faceWin->loadFromFile("images/face_win.png");

    debugTexture = new sf::Texture;
    debugSprite = new sf::Sprite;
    debugTexture->loadFromFile("images/debug.png");

    testTexture1 = new sf::Texture;
    testSprite1 = new sf::Sprite;
    testTexture1->loadFromFile("images/test_1.png");

    testTexture2 = new sf::Texture;
    testSprite2 = new sf::Sprite;
    testTexture2->loadFromFile("images/test_2.png");

    digit1 = new sf::Sprite;
    digit2 = new sf::Sprite;
    scoreboard0 = new sf::Texture;
    scoreboard0->loadFromFile("images/digits.png", sf::Rect<int>(0, 0, 21, 32));
    scoreboard1 = new sf::Texture;
    scoreboard1->loadFromFile("images/digits.png", sf::Rect<int>(21, 0, 21, 32));
    scoreboard2 = new sf::Texture;
    scoreboard2->loadFromFile("images/digits.png", sf::Rect<int>(42, 0, 21, 32));
    scoreboard3 = new sf::Texture;
    scoreboard3->loadFromFile("images/digits.png", sf::Rect<int>(63, 0, 21, 32));
    scoreboard4 = new sf::Texture;
    scoreboard4->loadFromFile("images/digits.png", sf::Rect<int>(84, 0, 21, 32));
    scoreboard5 = new sf::Texture;
    scoreboard5->loadFromFile("images/digits.png", sf::Rect<int>(105, 0, 21, 32));
    scoreboard6 = new sf::Texture;
    scoreboard6->loadFromFile("images/digits.png", sf::Rect<int>(126, 0, 21, 32));
    scoreboard7 = new sf::Texture;
    scoreboard7->loadFromFile("images/digits.png", sf::Rect<int>(147, 0, 21, 32));
    scoreboard8 = new sf::Texture;
    scoreboard8->loadFromFile("images/digits.png", sf::Rect<int>(168, 0, 21, 32));
    scoreboard9 = new sf::Texture;
    scoreboard9->loadFromFile("images/digits.png", sf::Rect<int>(189, 0, 21, 32));
    textures.push_back(scoreboard0);
    textures.push_back(scoreboard1);
    textures.push_back(scoreboard2);
    textures.push_back(scoreboard3);
    textures.push_back(scoreboard4);
    textures.push_back(scoreboard5);
    textures.push_back(scoreboard6);
    textures.push_back(scoreboard7);
    textures.push_back(scoreboard8);
    textures.push_back(scoreboard9);
    for (unsigned int x = 0; x < 25; x++) {
        for (unsigned int y = 0; y < 16; y++) {
            tiles[x][y] = new Tile;
            tiles[x][y]->setX(x);
            tiles[x][y]->setY(y);
        }
    }

    std::map<int, int> mineMap = generateRandomVector();
    generateMines(mineMap);

    calculateAdjacent();
}

void Board::reset() {
    numMines = 0;
    numClicked = 0;
    numFlagged = 0;
    gameLost = false;
    gameWon = false;

    for (auto& tile : tiles) {
        for (auto& j : tile) {
            delete j;
        }
    }

    for (unsigned int x = 0; x < 25; x++) {
        for (unsigned int y = 0; y < 16; y++) {
            tiles[x][y] = new Tile;
            tiles[x][y]->setX(x);
            tiles[x][y]->setY(y);
        }
    }
}

std::map<int, int> Board::generateRandomVector() {
    std::map<int, int> ret;

    for (unsigned int i = 0; i < 400; i++) {
        ret[i] = 0;
    }
    int numGenerated = 0;
    while (numGenerated < 50) {
        int gen = rand() % 400;
        if (ret[gen] == 0) {
            numGenerated++;
            ret[gen] = 1;
        }
    }

    return ret;
}

std::map<int, int> Board::loadMinesFromFile(std::string filepath) {
    std::map<int, int> ret;
    std::ifstream file(filepath);
    std::string line;

    int count = 0;
    for (unsigned int i = 0; i < 16; i++) {
        getline(file, line);
        for (unsigned int j = 0; j < 25; j++) {
            int mine = std::stoi(line.substr(j, 1));
            ret[count] = mine;
            count++;
        }
    }
    return ret;
}

void Board::generateMines(std::map<int, int> mineMap) {
    for (unsigned int x = 0; x < 25; x++) {
        for (unsigned int y = 0; y < 16; y++) {
            Tile* tile = tiles[x][y];
            int mine = y * 25 + x;
            tile->setMine(mineMap[mine] != 0);
            if (mineMap[mine] == 1) numMines++;
        }
    }
}

void Board::calculateAdjacent() {
    for (unsigned int x = 0; x < 25; x++) {
        for (unsigned int y = 0; y < 16; y++) {
            int numAdjacent = 0;
            if (x > 0) {
                if (tiles[x - 1][y]->getMine()) numAdjacent++;
            }
            if (x < 24) {
                if (tiles[x + 1][y]->getMine()) numAdjacent++;
            }
            if (y > 0) {
                if (tiles[x][y - 1]->getMine()) numAdjacent++;
            }
            if (y < 15) {
                if (tiles[x][y + 1]->getMine()) numAdjacent++;
            }
            if (x > 0 && y > 0) {
                if (tiles[x - 1][y - 1]->getMine()) numAdjacent++;
            }
            if (x > 0 && y < 15) {
                if (tiles[x - 1][y + 1]->getMine()) numAdjacent++;
            }
            if (x < 24 && y > 0) {
                if (tiles[x + 1][y - 1]->getMine()) numAdjacent++;
            }
            if (x < 24 && y < 15) {
                if (tiles[x + 1][y + 1]->getMine()) numAdjacent++;
            }
            tiles[x][y]->setNumAdjacentMines(numAdjacent);
        }
    }
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

Tile::Tile() {
    tileTexture = new sf::Texture;
    if (!tileTexture->loadFromFile("images/tile_hidden.png")) {
        std::cout << "Error loading hidden tile texture.";
    }
    tileSprite = new sf::Sprite;

    flagTexture = new sf::Texture;
    flagTexture->loadFromFile("images/flag.png");
    flagSprite = new sf::Sprite;
    flagSprite->setTexture(*flagTexture);
}

void Tile::draw(sf::RenderWindow* window, bool debugMode) {
    tileSprite->setTexture(*tileTexture);
    tileSprite->setPosition(xPixel, yPixel);
    window->draw(*tileSprite);

    if (flagged) {
        flagSprite->setPosition(xPixel, yPixel);
        window->draw(*flagSprite);
    } if ((debugMode && mine) || (clicked && mine)) {
        mineSprite->setTexture(*mineTexture);
        mineSprite->setPosition(xPixel, yPixel);
        window->draw(*mineSprite);
    } else if (clicked && mineTexture && numAdjacentMines > 0) {
        mineSprite->setTexture(*mineTexture);
        mineSprite->setPosition(xPixel, yPixel);
        window->draw(*mineSprite);
    }
}

void Tile::setX(int x) {
    xPos = x;
    xPixel = 32 * x;
}

void Tile::setY(int y) {
    yPos = y;
    yPixel = 32 * y;
}

void Tile::click() {
    if (flagged || clicked) {
        return;
    }

    clicked = true;

    if (mine) {
        return;
    }

    tileTexture->loadFromFile("images/tile_revealed.png");
}

void Tile::setNumAdjacentMines(int num) {
    numAdjacentMines = num;
    if (mine) {
        mineTexture = new sf::Texture;
        mineTexture->loadFromFile("images/mine.png");
        mineSprite = new sf::Sprite;
    } else if (numAdjacentMines > 0) {
        mineTexture = new sf::Texture;
        mineTexture->loadFromFile(std::string("images/number_") + std::to_string(num) + ".png");
        mineSprite = new sf::Sprite;
    }
}

void Tile::flag() {
    if (clicked) {
        return;
    }
    flagged = !flagged;
}
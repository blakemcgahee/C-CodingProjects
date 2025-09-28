#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include "Tile.h"

class Board {
public:
    Board() {};
    void click(int x, int y, bool left) {};
    void clickTile(int x, int y);
    Tile* getTile(int x, int y);
    void draw(sf::RenderWindow* window) {};

private:
    std::map<int, int> generateRandomVector();
    std::map<int, int> loadMinesFromFile(std::string filepath);
    void generateMines(std::map<int, int> mineMap);
    void calculateAdjacent();
    void checkWon();
    Tile* tiles[25][16]; 
    int numMines = 0;
    int numClicked = 0;
    int numFlagged = 0;
    bool gameLost = false;
    bool gameWon = false;
    void end();
    void reset();
    bool debugMode = false;
    sf::Texture* faceHappy;
    sf::Texture* faceLose;
    sf::Texture* faceWin;
    sf::Sprite* resetButton;
    sf::Texture* debugTexture;
    sf::Sprite* debugSprite;
    sf::Texture* testTexture1;
    sf::Sprite* testSprite1;
    sf::Texture* testTexture2;
    sf::Sprite* testSprite2;
    sf::Texture* scoreboard0;
    sf::Texture* scoreboard1;
    sf::Texture* scoreboard2;
    sf::Texture* scoreboard3;
    sf::Texture* scoreboard4;
    sf::Texture* scoreboard5;
    sf::Texture* scoreboard6;
    sf::Texture* scoreboard7;
    sf::Texture* scoreboard8;
    sf::Texture* scoreboard9;
    sf::Sprite* digit1;
    sf::Sprite* digit2;
    std::vector<sf::Texture*> textures;
};
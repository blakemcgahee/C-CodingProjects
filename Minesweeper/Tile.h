#include <SFML/Graphics.hpp>
#include <vector>

class Tile {
public:
    Tile();

    void draw(sf::RenderWindow* window, bool debugMode);
    void click();
    void flag();
    bool getClicked() { return clicked; }
    bool getFlagged() { return flagged; }
    void setMine(bool val) { mine = val; }
    bool getMine() { return mine; }
    int getX() { return xPos; }
    int gety() { return yPos; }
    void setX(int x); 
    void setY(int y); 
    float getXPixel() { return xPixel; }
    float getYPixel() { return yPixel; }
    void setNumAdjacentMines(int num);
    int getNumAdjacentMines() { return numAdjacentMines; }

private:
    int xPos;
    int yPos;

    float xPixel;
    float yPixel;

    bool mine = false;
    bool flagged = false;
    bool clicked = false;

    int numAdjacentMines;

    sf::Texture* tileTexture;
    sf::Sprite* tileSprite;

    sf::Texture* mineTexture; 
    sf::Sprite* mineSprite;

    sf::Texture* flagTexture; 
    sf::Sprite* flagSprite;
};

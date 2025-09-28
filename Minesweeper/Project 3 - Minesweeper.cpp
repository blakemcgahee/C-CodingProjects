#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Board.h"


int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Minesweeper");
    Board board;
    while (window->isOpen())
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                bool leftClick = (event.mouseButton.button == sf::Mouse::Left);
                board.click(event.mouseButton.x, event.mouseButton.y, leftClick);
            }
        }

        window->clear();
        board.draw(window);
        window->display();
    }
}
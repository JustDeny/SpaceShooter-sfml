#include <SFML/Graphics.hpp>
#include "GameLoop.h"
#include "Menu.h"
#include <ctime>

int main()
{
    srand((unsigned int)time(NULL));
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Space Shooter", sf::Style::Close
        | sf::Style::Titlebar);
    GameLoop* gameLoop = new GameLoop(window);
    Menu *menu = new Menu(window);
    while (1)
    {
        menu->Run();
        window->clear();
        if (!window->isOpen())
            break;
        gameLoop->Run();
        window->clear();
        menu->Reset();
        gameLoop->Reset();
    }
    return 0;
}
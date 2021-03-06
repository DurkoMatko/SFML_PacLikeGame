#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "include/PlayerChibi.h"
#include "include/Board.h"
#include "include/Menu.h"
#include "include/Game.h"


using namespace std;
using namespace sf;

int main()
{
    //variables for navigation of player

    /// Game window
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "PacLikeGame");
    window.setPosition(sf::Vector2i(200,0));
    Menu menu;

    menu.show(window);

    return EXIT_SUCCESS  ;
}

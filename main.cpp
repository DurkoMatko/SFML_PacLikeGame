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
    Vector2u wSize(WIDTH, HEIGHT);
    window.setPosition(sf::Vector2i(200,0));
    Menu menu(wSize.x,wSize.y);

    Keyboard keyboard;

    ///player picture
    PlayerChibi player;
    player.defineChibi("chibi4.png",wSize);

    ///Board + background + initial view
    Board board(0,50,500);
    board.setBackground("floor.jpg",window.getSize());
    board.resetView(FloatRect(0,0,wSize.x,wSize.y));
    board.setViewport(FloatRect(0,0,1.0f,1.0f));

    window.setKeyRepeatEnabled(true);


    ///MENU LOOP
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
             switch(event.type){
                case Event::KeyReleased:
                    if(event.key.code==Keyboard::Up){
                        menu.MoveUp();
                        cout << "Up" << endl;
                    }
                    else if(event.key.code==Keyboard::Down){
                        menu.MoveDown();
                        cout << "Down" << endl;
                    }
                    else if(event.key.code==Keyboard::Return){
                        switch(menu.getPressedItem()){
                            case 0:{
                                cout << "New game" << endl;
                                Game game;
                                game.RunGame(window);
                                cout << "dewdwd" << endl;
                                break;
                            }
                            case 1:
                                cout << "Options" << endl;
                                break;
                            case 2:
                                window.close();
                                break;
                        }
                    }
                    break;
                case Event::Closed:
                    window.close();
                    break;
             }
        }
        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}

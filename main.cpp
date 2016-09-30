#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "include/PlayerChibi.h"
#include "include/Board.h"

using namespace std;
using namespace sf;

int main()
{
    //variables for navigation of player
    enum Directions{DOWN,LEFT,RIGHT,UP};
    Vector2i source(1,DOWN);


    Board board(0,50,500);

    //float frameCounter = 0, switchFrame=50, frameSpeed = 500;
    //bool updateFrame;

    // Game window
    RenderWindow window(VideoMode(1200, 800), "SFML works!");
    Vector2u wSize(1200,800);
    window.setPosition(sf::Vector2i(200,0));

    string display="";
    Keyboard keyboard;

    //player picture
    PlayerChibi player;
    player.defineChibi("chibi4.png",wSize);

    //background picture
    board.setBackground("floor.jpg",window.getSize());
    /*Texture bTexture;
    bTexture.setSmooth(true);
    bTexture.setRepeated(true);
    if(!bTexture.loadFromFile("floor.jpg")){
        cout << "Not able to load background image" << endl;
    }

    RectangleShape backgroundRectangle;
    backgroundRectangle.setSize(Vector2f(window.getSize().x*2*10,window.getSize().y*2*10));     //2times bigger than screen...*10 because of scale
    backgroundRectangle.scale(Vector2f(0.1,0.1));
    int xBackgroundShift = window.getSize().x/2;        //dont know why but value needs to be saved in variable first
    int yBackgroundShift = window.getSize().y/2;
    backgroundRectangle.setPosition(-xBackgroundShift,-yBackgroundShift);
    backgroundRectangle.setOutlineColor(Color::Blue);
    backgroundRectangle.setOutlineThickness(50.0f);
    backgroundRectangle.setTexture(&bTexture);
    backgroundRectangle.setTextureRect(IntRect(0,0,window.getSize().x*2*10,window.getSize().y*2*10));*/

    ///VIEW
    //View view;
    //view.reset(FloatRect(0,0,wSize.x,wSize.y));
    //view.setViewport(FloatRect(0,0,1.0f,1.0f));
    board.resetView(FloatRect(0,0,wSize.x,wSize.y));
    board.setViewport(FloatRect(0,0,1.0f,1.0f));

    window.setKeyRepeatEnabled(true);
    while (window.isOpen())     //main game loop
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::GainedFocus:
                    cout << "Window active" << endl;
                    break;
                case Event::LostFocus:
                    cout << "Window NOT active" << endl;
                    break;
                case Event::Resized:
                    cout << "Width: " << event.size.width << "Height: " << event.size.height<< endl;
                    break;
                case Event::TextEntered:
                    if(event.text.unicode!=8)
                        display += (char) event.text.unicode;
                    else
                        display = display.substr(0,display.length()-1);
                    system("clear");
                    cout << display << endl;
                    break;
                case Event::KeyPressed:
                    if(event.key.code == keyboard.Escape){
                        window.close();
                        break;
                    }
            }
        }
        //mouse.isButtonPressed(mouse.Left))

        ///GETTING THE DIRECTION OF MOVEMENT FROM KEYBOARD ARROWS
        if(keyboard.isKeyPressed(keyboard.Up)){
            source.y=UP;
            //frameCounter += frameSpeed*clock.restart().asSeconds();
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(0,-2));
        }
        else if(keyboard.isKeyPressed(keyboard.Down)){
            source.y=DOWN;
            //frameCounter += frameSpeed*clock.restart().asSeconds();
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(0,2));
        }
        else if(keyboard.isKeyPressed(keyboard.Right)){
            source.y=RIGHT;
            //frameCounter += frameSpeed*clock.restart().asSeconds();
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(2,0));
        }
        else if(keyboard.isKeyPressed(keyboard.Left)){
            source.y=LEFT;
            //frameCounter += frameSpeed*clock.restart().asSeconds();
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(-2,0));
        }


        ///MOVING VIEW
        if(player.getPosition().x < -604){
            if(player.getPosition().y>406 || player.getPosition().y<-406){}
            else{
                board.resetView(FloatRect(-604,player.getPosition().y,wSize.x,wSize.y));
            }
        }
        else if(player.getPosition().x>604)
            if(player.getPosition().y>406 || player.getPosition().y<-406){}
            else{
                board.resetView(FloatRect(604,player.getPosition().y,wSize.x,wSize.y));
            }
        else if(player.getPosition().y>406)
            board.resetView(FloatRect(player.getPosition().x,406,wSize.x,wSize.y));
        else if(player.getPosition().y<-406)
            board.resetView(FloatRect(player.getPosition().x,-406,wSize.x,wSize.y));
        else{
            board.resetView(FloatRect(player.getPosition().x,player.getPosition().y,wSize.x,wSize.y));
        }


        ///CHANGING CHIBI
        if(board.getFrameCounter() >=board.getSwitchFrame()){
            board.setFrameCounter(0);
            //animation...each cycle shifts displayed chibi by 64pixels to the right...if size of picture is smaller than current pixel position,
            // then go again from pixel 0.
            source.x++;
            if(source.x*64 >= player.getPlayerTexture().getSize().x){
                source.x=0;
            }
        }


        window.setView(board.getView());

        window.draw(board.getBackgroundRectangle());
        player.setTexture(IntRect(source.x * 64, source.y *110, 64, 110));   //(start cropping X, start cropping Y, size in X, size in Y direction)
        window.draw(player.getPlayerImage());
        player.printCurrentPosition();
        window.display();
        window.clear();

    }

    return 0;
}

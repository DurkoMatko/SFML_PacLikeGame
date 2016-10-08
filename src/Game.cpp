#include "Game.h"
#include "Menu.h"
#include "Enemy.h"
#include "Board.h"
#include "PlayerChibi.h"
#include <string>
#include <stdlib.h>
#include <iostream>

Game::Game()
{
    escape=false;
}

Game::~Game()
{
    //dtor
}

void Game::RunGame(RenderWindow &window){
    Keyboard keyboard;
    string display = "";
    Vector2i source(1,DOWN);

    ///player picture
    PlayerChibi player;
    player.defineChibi("chibi4.png",Vector2u(WIDTH,HEIGHT));

    ///Board + background + initial view
    Board board(0,50,500);
    board.setBackground("floor.jpg",window.getSize());
    board.resetView(FloatRect(0,0,WIDTH,HEIGHT));
    board.setViewport(FloatRect(0,0,1.0f,1.0f));

    ///Enemies
    srand(time(0));   //clock for random position generator
    vector<Enemy> enemiesVector;
    enemiesVector.resize(1);

    window.setKeyRepeatEnabled(true);

    while (window.isOpen() && !escape)     //main game loop
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
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
                    else{
                        display = display.substr(0,display.length()-1);
                    }
                    system("clear");
                    cout << display << endl;
                    break;
                case Event::KeyPressed:
                    if(event.key.code == keyboard.Escape){
                        escape=true;
                        break;
                    }
            }
        }

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


        ///MOVE EACH ENEMY IN PLAYER DIRECTION
        for(int i=0;i<enemiesVector.size();i++){
            enemiesVector[i].chasePlayer(player.getRelativePosition(),player.getPicturePosition());
        }



        ///MOVING VIEW
        board.moveViewWithPlayer(player.getRelativePosition(),Vector2u(WIDTH,HEIGHT));



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

        if(escape==true){       //if NewGame chosen again than reset view to the middle
                board.resetView(FloatRect(0, 0, WIDTH, HEIGHT));
        }
        window.setView(board.getView());

        ///DRAW STUFF
        window.draw(board.getBackgroundRectangle());
        for(int i=0;i<enemiesVector.size();i++){
            window.draw(enemiesVector[i].getEnemyPicture());
        }
        player.setTexture(IntRect(source.x * 64, source.y *110, 64, 110));   //(start cropping X, start cropping Y, size in X, size in Y direction)
        window.draw(player.getPlayerImage());

        ///PRINT POSITIONS
        player.printCurrentPosition();
        for(int i=0;i<enemiesVector.size();i++){
            enemiesVector[i].printCurrentPosition();
        }
        cout<<endl;

        window.display();
        window.clear();

    }
}

void Game::dd(){
}

#include "PlayerChibi.h"
#include "MyException.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

PlayerChibi::PlayerChibi()
{
    //ctor
}

PlayerChibi::~PlayerChibi()
{
    //dtor
}


void PlayerChibi::defineChibi(){
    pTexture.setSmooth(true);
    try{
        if(!pTexture.loadFromFile("Images/chibi4.png")){
            throw MyFontException();
        }
    }
    catch(MyFontException& ex){
        cout << ex.what(1,"chibi4.png") << endl;
        exit(EXIT_FAILURE);
        //abort();
        //_Exit(EXIT_FAILURE);
    }
    playerImage.setTexture(pTexture,true);
    playerImage.setPosition(WIDTH/2 -32,HEIGHT/2 - 55);   //coordinates of left upper corner need to be shifted by half of picture size

    relativePosition.x=0;
    relativePosition.y=0;
}

Vector2i PlayerChibi::getRelativePosition(){
    return relativePosition;
}

void PlayerChibi::setPosition(Vector2i newPosition){
    relativePosition.x = newPosition.x;
    relativePosition.y = newPosition.y;
}
void PlayerChibi::movePlayer(Vector2i change){
    int xLimit = X_MOVEMENT_LIMIT;
    int yLimit = Y_MOVEMENT_LIMIT;
    if(relativePosition.x + change.x <xLimit && relativePosition.x + change.x > -xLimit &&
       relativePosition.y + change.y < (yLimit-23) && relativePosition.y + change.y > -yLimit ){        //23 because feet have different position than head
        playerImage.move(change.x,change.y);
        relativePosition.x += change.x;
        relativePosition.y += change.y;
    }
}
void PlayerChibi::setTexture(IntRect pictureRectangle){
    playerImage.setTextureRect(pictureRectangle);
}
Sprite PlayerChibi::getPlayerImage(){
    return playerImage;
}
Texture PlayerChibi::getPlayerTexture(){
    return pTexture;
}
Vector2f PlayerChibi::getPicturePosition(){
    return playerImage.getPosition();
}

void PlayerChibi::printCurrentPosition(){
     cout << "Player pic position:X " << playerImage.getPosition().x << ", Y  " << playerImage.getPosition().y << endl;
     cout << "Player relative position:X " << relativePosition.x << ", Y  " << relativePosition.y << endl;
}

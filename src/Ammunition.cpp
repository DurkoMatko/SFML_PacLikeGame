#include "Ammunition.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"



using namespace std;

Ammunition::Ammunition()
{
    aTexture.setSmooth(true);
    if(!aTexture.loadFromFile("Images/ammunition.png")){
        cout << "Not able to load ammunition image" << endl;
    }
    ammunitionImage.setTexture(aTexture,true);
    //ammunitionImage.setPosition(Vector2f(WIDTH/2,HEIGHT/2));
    ammunitionImage.scale(0.4,0.4);
    this->setRandomPosition();
}

Ammunition::~Ammunition()
{
    //dtor
}

Sprite Ammunition::getAmmunitionPicture(){
    return this->ammunitionImage;
}

Vector2f Ammunition::setRandomPosition(){
    Vector2f position;

    position.x= MIN_X + (rand() % (MAX_X - MIN_X + 1));             //generate random number formula
    position.y= MIN_Y + (rand() % (MAX_Y - MIN_Y + 1));

    cout << position.x << " " << position.y << endl;
    ammunitionImage.setPosition(position);
	return position;
}

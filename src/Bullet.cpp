#include "Bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

Bullet::Bullet()
{
    //ctor
}

Bullet::Bullet(int direction,Vector2f playerPicturePosition)
{

    this->bTexture.setSmooth(true);
    if(!this->bTexture.loadFromFile("Images/bullet2.png")){
        cout << "Not able to load bullet image" << endl;
    }
    this->bulletImage.setTexture(this->bTexture);
    this->bulletImage.setPosition(playerPicturePosition.x+20,playerPicturePosition.y+40);   //coordinates of left upper corner need to be shifted by half of picture size
    this->bulletImage.scale(0.13,0.13);

    switch(direction){
        case 0: //down
            directionVector=Vector2f(0,1);
            bulletImage.rotate(-90);
            break;
        case 1: //left
            directionVector=Vector2f(-1,0);
            break;
        case 3: //up
            directionVector=Vector2f(0,-1);
            bulletImage.rotate(90);
            break;
        case 2: //right
            directionVector=Vector2f(1,0);
            bulletImage.rotate(180);
            break;
    }
}

Bullet::~Bullet()
{
    //dtor
}

Sprite Bullet::getBulletPicture(){
    return bulletImage;
}

void Bullet::moveBullet(){
    int speed = 3;
    bulletImage.move(directionVector.x*speed,directionVector.y*speed);
}

void Bullet::printCurrentPosition(){
    cout << "Bullet position: " << bulletImage.getPosition().x << " " << bulletImage.getPosition().y << endl;
}

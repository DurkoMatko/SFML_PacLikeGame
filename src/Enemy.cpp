#include "Enemy.h"
#include "Board.h"


using namespace std;
using namespace sf;

Enemy::Enemy()
{
    eTexture.setSmooth(true);
    if(!eTexture.loadFromFile("Images/enemy2.png")){
        cout << "Not able to load enemy image" << endl;
    }
    enemyImage.setTexture(eTexture,true);
    enemyImage.setPosition(this->randomPosition());   //coordinates of left upper corner need to be shifted by half of picture size
    enemyImage.scale(0.17,0.17);

    relativePosition.x=enemyImage.getPosition().x-(WIDTH/2-32);
    relativePosition.y=enemyImage.getPosition().y-(HEIGHT/2-55);
}

Enemy::~Enemy()
{
    //dtor
}

Sprite Enemy::getEnemyPicture(){
    return enemyImage;
}

Vector2f Enemy::randomPosition(){
    Vector2f position;

    position.x= MIN_X + (rand() % (MAX_X - MIN_X + 1));             //generate random number formula
    position.y= MIN_Y + (rand() % (MAX_Y - MIN_Y + 1));
	return position;
}

void Enemy::printCurrentPosition(){
     cout << "Enemy pic position:X " << enemyImage.getPosition().x << ", Y  " << enemyImage.getPosition().y << endl;
     cout << "Enemy relative position:X " << relativePosition.x << ", Y  " << relativePosition.y << endl;
}


bool Enemy::chasePlayer(Vector2i playerRelativePosition,Vector2f playerPicturePosition,int enemySpeed){
    signed int x=playerRelativePosition.x - relativePosition.x;         // vector in x direction
    signed int y=playerRelativePosition.y+20 - relativePosition.y;      //vector in y direction
    if(x*x+y*y>HYPOTENUSE*HYPOTENUSE || x*x+y*y<-HYPOTENUSE*HYPOTENUSE){    //so v is bigger than defined minimal hypotenuse
        float v=sqrt(x*x + y*y);
        float unitx=x/v;
        float unity=y/v;
        this->moveEnemy(Vector2f(unitx*(1+enemySpeed/10),unity*(1+enemySpeed/10)));
        return false;
    }
    return true;
}

void Enemy::moveEnemy(Vector2f change){
    enemyImage.move(change.x,change.y);
    relativePosition.x += change.x;
    relativePosition.y += change.y;
}

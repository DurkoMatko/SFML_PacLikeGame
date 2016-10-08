#include "Enemy.h"
#include "Board.h"


using namespace std;
using namespace sf;

Enemy::Enemy()
{
    eTexture.setSmooth(true);
    if(!eTexture.loadFromFile("enemy2.png")){
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
    cout << rand() << endl;
    Vector2f position;

    position.x= 0 + (rand() % (WIDTH - 0 + 1));
    position.y= 0 + (rand() % (HEIGHT - 0 + 1));
    cout << position.x << " " << position.y << endl;
	return position;
}

void Enemy::printCurrentPosition(){
     cout << "Enemy pic position:X " << enemyImage.getPosition().x << ", Y  " << enemyImage.getPosition().y << endl;
     cout << "Enemy relative position:X " << relativePosition.x << ", Y  " << relativePosition.y << endl;
}


void Enemy::chasePlayer(Vector2i playerRelativePosition,Vector2f playerPicturePosition){
    signed int x=playerRelativePosition.x - relativePosition.x;
    cout << "x:" << x<< endl;
    signed int y=playerRelativePosition.y - relativePosition.y;
    cout << "y:" << y<< endl;
    float v=sqrt(x*x + y*y);
    cout << "v:" << v<< endl;
    float unitx=x/v;
    cout << "unitx:" << unitx<< endl;
    float unity=y/v;
    cout << "unity:" << unity<< endl;
    this->moveEnemy(Vector2f(unitx,unity));
}

void Enemy::moveEnemy(Vector2f change){
    enemyImage.move(change.x,change.y);
    relativePosition.x += change.x;
    relativePosition.y += change.y;
}

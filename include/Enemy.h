#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

class Enemy
{
    public:
        Enemy();
        virtual ~Enemy();
        Sprite getEnemyPicture();
        Vector2f randomPosition();
        void printCurrentPosition();
        void chasePlayer(Vector2i playerRelativePosition,Vector2f playerPicturePosition);
        void moveEnemy(Vector2f change);
    protected:
    private:
        Vector2f relativePosition;
        Texture eTexture;
        Sprite enemyImage;
};

#endif // ENEMY_H

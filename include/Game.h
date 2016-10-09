#ifndef GAME_H
#define GAME_H

#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "PlayerChibi.h"


using namespace std;
using namespace sf;

class Game
{
    public:
        enum Directions{DOWN,LEFT,RIGHT,UP};
        Game();
        virtual ~Game();
        void runGame(RenderWindow &window);
        void drawAllMovingObjects(RenderWindow &window,Vector2i source);
        void printPositions();
        void checkBulletHits();
    protected:
    private:
        bool escape;
        vector<Enemy> enemiesVector;
        PlayerChibi player;
        Keyboard keyboard;
        vector<Bullet> bulletsVector;

};

#endif // GAME_H

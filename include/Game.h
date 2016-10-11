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
        void checkBulletsInView(View view);
        bool readAndSetSettings(string filename);
    protected:
    private:
        bool escape;
        int enemyCount;
        int enemySpeed;
        int score;
        vector<Enemy*> enemiesVector;
        PlayerChibi player;
        Keyboard keyboard;
        vector<Bullet*> bulletsVector;      //needs to be a pointer because of scope - texture is created in different scope

};

#endif // GAME_H

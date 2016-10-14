#ifndef GAME_H
#define GAME_H

#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "PlayerChibi.h"
#include "Ammunition.h"


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
        void displayScore(RenderWindow &window, View view);
        void displayBullets(RenderWindow &window, View view);
        bool checkHighscore();
        void showLosingAnimation(RenderWindow &window,Board &board,Vector2i source);
        void checkAmmunitionBox();
        void calculateAndDrawPointer(RenderWindow &window, View view);
        pair<float,float> findEquation(float x1, float y1, float x2, float y2);
        Vector2f findIntersectionPoint(float slope1,float intersect1, float slope2, float intersect2);
    protected:
    private:
        bool escape;
        int enemyCount;
        int enemySpeed;
        int score;
        int remainingBullets;
        vector<Enemy*> enemiesVector;
        PlayerChibi player;
        Keyboard keyboard;
        vector<Bullet*> bulletsVector;      //needs to be a pointer because of scope - texture is created in different scope
        Font font;
        Ammunition ammunitionBox;

};

#endif // GAME_H

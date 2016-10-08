#ifndef GAME_H
#define GAME_H

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
    protected:
    private:
        bool escape;
        vector<Enemy> enemiesVector;
        PlayerChibi player;
        Keyboard keyboard;

};

#endif // GAME_H

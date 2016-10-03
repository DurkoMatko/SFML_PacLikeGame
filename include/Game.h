#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Game
{
    public:
        enum Directions{DOWN,LEFT,RIGHT,UP};
        Game();
        virtual ~Game();
        void RunGame(RenderWindow &window);
        void dd();
    protected:
    private:
        bool escape;
};

#endif // GAME_H

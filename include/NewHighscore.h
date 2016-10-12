#ifndef NEWHIGHSCORE_H
#define NEWHIGHSCORE_H

#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


class NewHighscore
{
    public:
        NewHighscore(int atSpeed);
        virtual ~NewHighscore();
        void enterName(RenderWindow &window, Font font, View view);
        void loadHighscore();
        void insertNewScore(int newScore);
    protected:
    private:
        int playedAtSpeed;
        RectangleShape border;
        string nick;
        Text nickText;
        map<int,string> loadedHighscores;
        bool escape;
};

#endif // NEWHIGHSCORE_H

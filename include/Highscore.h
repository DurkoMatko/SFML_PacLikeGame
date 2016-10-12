#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <SFML/Graphics.hpp>
#include "IncreaseSettingsButton.h"
#include "DecreaseSettingsButton.h"
#include "Board.h"
#include <string>
#include <iostream>

#define NUMBER_OF_HIGHSCORES 8

using namespace sf;
using namespace std;

class Highscore
{
    public:
        Highscore();
        virtual ~Highscore();
        void show(RenderWindow &window);
        void reloadHighscore();
        void draw(RenderWindow &window);
    protected:
    private:
        bool escape;
        int atSpeed;
        vector<Text> names;
        vector<Text> scores;
        Font font;
        Text title;
        Text subtitle;
        DecreaseSettingsButton lowerSpeedButton;
        IncreaseSettingsButton higherSpeedButton;
};

#endif // HIGHSCORE_H

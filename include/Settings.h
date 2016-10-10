#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "DecreaseSettingsButton.h"
#include "IncreaseSettingsButton.h"

#define NUMBER_OF_SETTING_ITEMS 4

using namespace sf;
using namespace std;

class Settings
{
    public:
        Settings();
        virtual ~Settings();
        void draw(RenderWindow &window);
        void show(RenderWindow &window);
        void MoveUp();
        void MoveDown();
        int getPressedItem();
    protected:
    private:
        bool escape;
        int selectedItemIndex;
        Font font;
        Text menu[NUMBER_OF_SETTING_ITEMS];
        Text title;
        vector<DecreaseSettingsButton*> decreaseButtons;
        vector<IncreaseSettingsButton*> increaseButtons;
};

#endif // SETTINGS_H

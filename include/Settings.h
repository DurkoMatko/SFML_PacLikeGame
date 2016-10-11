#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "DecreaseSettingsButton.h"
#include "IncreaseSettingsButton.h"
#include "tinyxml2.h"
#include "tinyxml.h"

#define NUMBER_OF_SETTING_ITEMS 4

using namespace sf;
using namespace std;
using namespace tinyxml2;

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
        void increaseValue();
        void decreaseValue();
        bool readSettings();
        bool saveChanges();
    protected:
    private:
        bool escape;
        int selectedItemIndex;
        Font font;
        Text menu[NUMBER_OF_SETTING_ITEMS];
        Text title;
        vector<Text> valuesToChange;
        vector<DecreaseSettingsButton*> decreaseButtons;
        vector<IncreaseSettingsButton*> increaseButtons;
        XMLDocument doc2;
};

#endif // SETTINGS_H

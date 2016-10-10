#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define NUMBER_OF_MENU_ITEMS 4

using namespace sf;
using namespace std;

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        void draw(RenderWindow &window);
        void MoveUp();
        void MoveDown();
        int getPressedItem();
        void show(RenderWindow &window);
    protected:
    private:
        int selectedItemIndex;
        Font font;
        Text menu[NUMBER_OF_MENU_ITEMS];
        Text title;
};

#endif // MENU_H

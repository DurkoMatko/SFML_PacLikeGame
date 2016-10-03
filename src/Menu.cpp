#include "Menu.h"

Menu::Menu(float width,float height)
{
    if(!font.loadFromFile("arial.ttf")){
        //handle error
    }

    vector<std::string> fields = {"New game", "Highscore","Exit"};
    selectedItemIndex=0;

    for(int i=0;i<NUMBER_OF_MENU_ITEMS;i++){
        menu[i].setFont(font);
        menu[i].setString(fields[i]);
        menu[i].setPosition(Vector2f(width/2-50,height/(NUMBER_OF_MENU_ITEMS)+50*i));

        if(selectedItemIndex==i){
            menu[i].setColor(Color::Red);
        }
        else{
            menu[i].setColor(Color::White);
        }
    }

    title.setFont(font);
    title.setString("PacLikeGame");
    title.setColor(Color::White);
    title.setCharacterSize(50);
    title.setPosition(width/2-130,70);

}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(RenderWindow &window){
    for (int i=0;i<NUMBER_OF_MENU_ITEMS; i++){
        window.draw(menu[i]);
    }
    window.draw(title);
}

void Menu::MoveUp(){
    if(selectedItemIndex-1>=0){         //check if in bounds
        menu[selectedItemIndex].setColor(Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(Color::Red);
    }
}

void Menu::MoveDown(){
    if(selectedItemIndex+1<NUMBER_OF_MENU_ITEMS){         //check if in bounds
        menu[selectedItemIndex].setColor(Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(Color::Red);
    }
}

int Menu::getPressedItem(){
    return selectedItemIndex;
}

#include "Menu.h"
#include "Game.h"
#include "Settings.h"
#include "Highscore.h"
#include "MyException.h"


Menu::Menu()
{
    try{
        if(!font.loadFromFile("arial.ttf")){
            throw MyFontException();
        }
    }
    catch(MyFontException& e){
        cout << e.what(1,"arial.ttf") << endl;
        exit(EXIT_FAILURE);
    }

    vector<std::string> fields = {"New game", "Settings","Highscore","Exit"};
    selectedItemIndex=0;

    for(int i=0;i<NUMBER_OF_MENU_ITEMS;i++){
        menu[i].setFont(font);
        menu[i].setString(fields[i]);
        menu[i].setPosition(Vector2f(WIDTH/2-50,HEIGHT/(NUMBER_OF_MENU_ITEMS)+50*i));

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
    title.setPosition(WIDTH/2-130,70);
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

Font Menu::getFont(){
    return font;
}

void Menu::show(RenderWindow &window){

    ///MENU LOOP
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
             switch(event.type){
                case Event::KeyReleased:
                    if(event.key.code==Keyboard::Up){
                        this->MoveUp();
                        cout << "Up" << endl;
                    }
                    else if(event.key.code==Keyboard::Down){
                        this->MoveDown();
                        cout << "Down" << endl;
                    }
                    else if(event.key.code==Keyboard::Return){
                        string chosenOption = menu[this->getPressedItem()].getString();
                        cout << chosenOption << endl;
                        switch(this->getPressedItem()){
                            case 0:{
                                Game game;
                                game.runGame(window);
                                break;
                            }
                            case 1:{
                                Settings settings;
                                settings.show(window);
                                break;
                            }
                            case 2:{
                                Highscore highscore;
                                highscore.show(window);
                                break;
                            }
                            case 3:
                                window.close();
                                break;
                        }
                    }
                    break;
                case Event::Closed:
                    window.close();
                    break;
             }
        }
        window.clear();
        this->draw(window);
        window.display();
    }
}

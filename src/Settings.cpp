#include "Settings.h"
#include "Board.h"
#include <iostream>

using namespace std;

Settings::Settings()
{
    escape=false;
    if(!font.loadFromFile("arial.ttf")){
        //handle error
    }

    vector<std::string> fields = {"Enemies number", "Enemies speed","Cancel","Save"};
    selectedItemIndex=0;

    for(int i=0;i<NUMBER_OF_SETTING_ITEMS;i++){
        menu[i].setFont(font);
        menu[i].setString(fields[i]);
        if(i<NUMBER_OF_SETTING_ITEMS-2){
            menu[i].setPosition(Vector2f(WIDTH/2-300,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i));                   //settings
            decreaseButtons.push_back(new DecreaseSettingsButton(WIDTH/2+100,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i + 20));    //buttons to decrease setting value
            increaseButtons.push_back(new IncreaseSettingsButton(WIDTH/2+300,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i + 20));    //buttons to decrease setting value
        }
        else{
            switch(i){
                case (NUMBER_OF_SETTING_ITEMS-2):
                    menu[i].setPosition(Vector2f(WIDTH/2-180,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*(i+1)));       //cancel
                    break;
                case (NUMBER_OF_SETTING_ITEMS-1):
                    menu[i].setPosition(Vector2f(WIDTH/2+120,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i));           //save
                    break;
            }
        }

        if(selectedItemIndex==i){
            menu[i].setColor(Color::Red);
        }
        else{
            menu[i].setColor(Color::White);
        }
    }

    title.setFont(font);
    title.setString("Settings");
    title.setColor(Color::White);
    title.setCharacterSize(50);
    title.setPosition(WIDTH/2-80,70);
}

Settings::~Settings()
{
    //dtor
}

void Settings::MoveUp(){
    if(selectedItemIndex-1>=0){         //check if in bounds
        menu[selectedItemIndex].setColor(Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(Color::Red);
    }
}

void Settings::MoveDown(){
    if(selectedItemIndex+1<NUMBER_OF_SETTING_ITEMS){         //check if in bounds
        menu[selectedItemIndex].setColor(Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(Color::Red);
    }
}

int Settings::getPressedItem(){
    return selectedItemIndex;
}

void Settings::draw(RenderWindow &window){
    for (int i=0;i<NUMBER_OF_SETTING_ITEMS; i++){       //setting names
        window.draw(menu[i]);
    }
    for(int i=0;i<decreaseButtons.size();i++){          //same number of decrease & increase buttons
        window.draw(decreaseButtons[i]->getButtonShape());
        window.draw(increaseButtons[i]->getButtonShape());
    }
    window.draw(title);
}

void Settings::show(RenderWindow &window){
    ///MENU LOOP
    while (window.isOpen() && !escape)
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
                                break;
                            }
                            case 1:{
                                break;
                            }
                            case 2:
                                escape=true;
                                break;
                            case 3:
                                escape=true;
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

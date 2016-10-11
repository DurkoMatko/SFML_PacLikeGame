#include "Settings.h"
#include "Board.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace tinyxml2;

Settings::Settings():doc2()
{

    this->readSettings();               //parses "GameSettings.xml"

    escape=false;
    if(!font.loadFromFile("arial.ttf")){
        //handle error
    }
    cout<<"edede";
    vector<std::string> fields = {"Enemies number", "Enemies speed","Cancel","Save"};
    selectedItemIndex=0;

    for(int i=0;i<NUMBER_OF_SETTING_ITEMS;i++){
        menu[i].setFont(font);
        menu[i].setString(fields[i]);
        if(i<NUMBER_OF_SETTING_ITEMS-2){
            menu[i].setPosition(Vector2f(WIDTH/2-300,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i));                   //settings
            decreaseButtons.push_back(new DecreaseSettingsButton(WIDTH/2+100,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i + 20));    //buttons to decrease setting value
            increaseButtons.push_back(new IncreaseSettingsButton(WIDTH/2+300,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i + 20));    //buttons to decrease setting value
            valuesToChange[i].setPosition(WIDTH/2+185,HEIGHT/(NUMBER_OF_SETTING_ITEMS)+50*i);
            valuesToChange[i].setFont(font);
            valuesToChange[i].setColor(Color::White);
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
        window.draw(valuesToChange[i]);
    }
    window.draw(title);
}

void Settings::increaseValue(){
    increaseButtons[selectedItemIndex]->setButtonColor(Color::Red);
    int oldValue;
    stringstream(valuesToChange[selectedItemIndex].getString()) >> oldValue;     //stream old value to get integer value
    valuesToChange[selectedItemIndex].setString(to_string(oldValue+1));
}

void Settings::decreaseValue(){
    decreaseButtons[selectedItemIndex]->setButtonColor(Color::Red);
    int oldValue;
    stringstream(valuesToChange[selectedItemIndex].getString()) >> oldValue;     //stream old value to get integer value
    valuesToChange[selectedItemIndex].setString(to_string(oldValue-1));
}

bool Settings::readSettings(){
    if(doc2.LoadFile("GameSettings.xml") != XML_SUCCESS){
        cout << "Error loading settings xml" << endl;
        return false;
    }
    XMLElement *pRoot = doc2.FirstChildElement("GameSettings");
    XMLElement *numberOfEnemiesNode,*speedNode;
    numberOfEnemiesNode = pRoot->FirstChildElement("numberOfEnemies");
    speedNode=pRoot->FirstChildElement("enemySpeed");
    /*TiXmlElement *pRoot, *numberOfEnemiesNode,*speedNode;
    pRoot = doc.FirstChildElement("GameSettings");
    numberOfEnemiesNode = pRoot->FirstChildElement("numberOfEnemies");
    speedNode = pRoot->FirstChildElement("enemySpeed");*/

    if(pRoot && numberOfEnemiesNode && speedNode)
    {
        Text number;
        number.setString(numberOfEnemiesNode->GetText());
        valuesToChange.push_back(number);
        Text speed;
        speed.setString(speedNode->GetText());
        valuesToChange.push_back(speed);
        return true;
    }
    return false;
}

bool Settings::saveChanges(){
    XMLElement *pRoot;
    pRoot = doc2.FirstChildElement("GameSettings");                                                  //get root node

    //numberOfEnemies
    pRoot->FirstChildElement("numberOfEnemies")->DeleteChildren();                                   //delete old value
    XMLText *newValue = doc2.NewText(valuesToChange[0].getString().toAnsiString().c_str());          //create new value as text
    pRoot->FirstChildElement("numberOfEnemies")->LinkEndChild(newValue);                             //insert new value

    //enemySpeed
    pRoot->FirstChildElement("enemySpeed")->DeleteChildren();                                   //delete old value
    newValue = doc2.NewText(valuesToChange[1].getString().toAnsiString().c_str());          //create new value as text
    pRoot->FirstChildElement("enemySpeed")->LinkEndChild(newValue);                             //insert new value

    return doc2.SaveFile("GameSettings.xml");
}

void Settings::show(RenderWindow &window){
    ///MENU LOOP
    while (window.isOpen() && !escape)
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case Event::KeyPressed:
                    if(event.key.code==Keyboard::Left && selectedItemIndex<NUMBER_OF_SETTING_ITEMS-2){
                        this->decreaseValue();
                        cout << "Decrease" << endl;
                    }
                    else if(event.key.code==Keyboard::Right  && selectedItemIndex<NUMBER_OF_SETTING_ITEMS-2){
                        this->increaseValue();
                        cout << "Increase" << endl;
                    }
                    break;

                case Event::KeyReleased:
                    if(event.key.code==Keyboard::Up){
                        this->MoveUp();
                        cout << "Up" << endl;
                    }
                    else if(event.key.code==Keyboard::Down){
                        this->MoveDown();
                        cout << "Down" << endl;
                    }
                    else if(event.key.code==Keyboard::Left && selectedItemIndex<NUMBER_OF_SETTING_ITEMS-2){
                        decreaseButtons[selectedItemIndex]->setButtonColor(Color::White);                       //set decrease button back to white
                    }
                    else if(event.key.code==Keyboard::Right  && selectedItemIndex<NUMBER_OF_SETTING_ITEMS-2){   //set decrease button back to white
                        increaseButtons[selectedItemIndex]->setButtonColor(Color::White);
                    }
                    else if(event.key.code==Keyboard::Return){
                        string chosenOption = menu[this->getPressedItem()].getString();
                        cout << chosenOption << endl;
                        switch(this->getPressedItem()){
                            case 2:
                                escape=true;
                                break;
                            case 3:
                                this->saveChanges();
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

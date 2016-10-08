#include "Menu.h"
#include "Game.h"


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
                        switch(this->getPressedItem()){
                            case 0:{
                                cout << "New game" << endl;
                                Game game;
                                game.runGame(window);
                                break;
                            }
                            case 1:
                                cout << "Options" << endl;
                                break;
                            case 2:
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

#include "Highscore.h"
#include "MyException.h"
#include "Board.h"
#include <fstream>

using namespace std;

Highscore::Highscore():lowerSpeedButton(WIDTH/2-150,HEIGHT/NUMBER_OF_HIGHSCORES+120), higherSpeedButton(WIDTH/2+150,HEIGHT/NUMBER_OF_HIGHSCORES+120)
{
    escape=false;
    atSpeed=1;
    try{
        if(!font.loadFromFile("arial.ttf")){
            throw MyFontException();
        }
    }
    catch(MyFontException& e){
        cout << e.what(1,"aria.ttf") << endl;
        exit(EXIT_FAILURE);
        //abort();
        //_Exit(EXIT_FAILURE);
    }


    scores.resize(NUMBER_OF_HIGHSCORES);
    names.resize(NUMBER_OF_HIGHSCORES);
    for(int i=0;i<NUMBER_OF_HIGHSCORES;i++){
        names[i].setFont(font);
        names[i].setColor(Color::White);
        names[i].setCharacterSize(30);
        names[i].setPosition(Vector2f(WIDTH/2-230,HEIGHT/NUMBER_OF_HIGHSCORES+25*i+200));

        scores[i].setFont(font);
        scores[i].setColor(Color::White);
        scores[i].setCharacterSize(30);
        scores[i].setPosition(Vector2f(WIDTH/2+170,HEIGHT/NUMBER_OF_HIGHSCORES+25*i+200));
    }

    title.setFont(font);
    title.setString("Highscores");
    title.setColor(Color::Red);
    title.setCharacterSize(50);
    title.setPosition(WIDTH/2-100,70);

    subtitle.setFont(font);
    subtitle.setColor(Color::White);
    subtitle.setCharacterSize(30);
    subtitle.setPosition(WIDTH/2-50,HEIGHT/NUMBER_OF_HIGHSCORES+100);

    this->reloadHighscore();
}

Highscore::~Highscore()
{
    //dtor
}

void Highscore::show(RenderWindow &window){
    while (window.isOpen() && !escape)
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case Event::KeyPressed:
                    if(event.key.code==Keyboard::Left){
                        if(atSpeed==1){        //circling the speeds
                            atSpeed=15;
                        }
                        else{
                            atSpeed -= 1;
                        }
                        lowerSpeedButton.setButtonColor(Color::Red);
                        cout << "Lower speed" << endl;
                    }
                    else if(event.key.code==Keyboard::Right){
                        if(atSpeed==15){        //circling the speeds
                            atSpeed=1;
                        }
                        else{
                            atSpeed += 1;
                        }
                        higherSpeedButton.setButtonColor(Color::Red);
                        cout << "Higher speed" << endl;
                    }
                    this->reloadHighscore();
                    break;
                case Event::KeyReleased:
                    if(event.key.code==Keyboard::Left){
                        lowerSpeedButton.setButtonColor(Color::White);                       //set decrease button back to white
                    }
                    else if(event.key.code==Keyboard::Right){   //set decrease button back to white
                        higherSpeedButton.setButtonColor(Color::White);                       //set decrease button back to white
                    }
                    else if(event.key.code==Keyboard::Escape){
                            escape=true;
                    }
                    break;
                case Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        if(!escape){
            this->draw(window);
            window.display();
        }
    }
}


void Highscore::reloadHighscore(){
    ifstream file("Highscores/Highscore_" + to_string(atSpeed) + ".txt");
    string str;
    int readScore;
    string player;
    int i=0;

    while (getline(file, str))
    {
        readScore =  atoi(str.substr(str.find(" ") + 1).c_str());
        player=str.substr(0,str.find(" "));
        scores[i].setString(to_string(readScore));
        names[i].setString(to_string(i+1)+". " + player);
        i++;
    }

    subtitle.setString("Speed " + to_string(atSpeed));
}

void Highscore::draw(RenderWindow &window){
    window.draw(title);
    window.draw(subtitle);
    window.draw(lowerSpeedButton.getButtonShape());
    window.draw(higherSpeedButton.getButtonShape());
    for(int i=0;i<NUMBER_OF_HIGHSCORES;i++){
        window.draw(scores[i]);
        window.draw(names[i]);
    }
}

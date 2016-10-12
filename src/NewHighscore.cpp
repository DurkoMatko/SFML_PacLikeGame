#include "NewHighscore.h"
#include "Board.h"
#include <fstream>

NewHighscore::NewHighscore(int atSpeed)
{
    border.setSize(Vector2f(WIDTH/2,60));           //60 seems enough - just random number
    border.setFillColor(Color::Black);
    border.setOutlineColor(Color::White);
    border.setOutlineThickness(5.0f);
    playedAtSpeed = atSpeed;
    this->loadHighscore();
}

NewHighscore::~NewHighscore()
{
    //dtor
}

void NewHighscore::enterName(RenderWindow &window, Font font, View view){
    Clock clock;
    Time time;
    border.setPosition(view.getCenter().x-WIDTH/4,view.getCenter().y-150);
    Text title;
    title.setFont(font);
    title.setString("New highscore!!!");
    title.setColor(Color::Red);
    title.setCharacterSize(50);
    title.setPosition(view.getCenter().x-180,view.getCenter().y-HEIGHT/2+70);

    nickText.setFont(font);
    nickText.setColor(Color::White);
    nickText.setCharacterSize(30);
    nickText.setPosition(view.getCenter().x-80,view.getCenter().y-150);

    while (window.isOpen() && !escape)     //main game loop
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case Event::KeyReleased:
                    if(event.key.code==Keyboard::Return){
                        escape=true;
                    }
                    break;
                case Event::TextEntered:
                    if(event.text.unicode!=8){
                        if(event.text.unicode>=65 && event.text.unicode<=122)
                            nick += (char)event.text.unicode;
                    }
                    else
                        nick = nick.substr(0,nick.length()-1);
                    nickText.setString(nick);
                    break;
            }
        }

        if((int)clock.getElapsedTime().asMilliseconds() % 100 >=50)
            title.setColor(Color::Green);
        else
            title.setColor(Color::Blue);
        window.clear();
        window.draw(title);
        window.draw(border);
        window.draw(nickText);
        window.display();
    }
}

void NewHighscore::loadHighscore(){
    ifstream file("Highscores/Highscore_" + to_string(playedAtSpeed) + ".txt");
    string str;
    int readScore;
    while (getline(file, str))
    {
        readScore =  atoi(str.substr(str.find(" ") + 1).c_str());
        loadedHighscores.insert(make_pair(readScore,str.substr(0,str.find(" "))));
    }
}

void NewHighscore::insertNewScore(int newScore){
    bool inserted = false;
    ofstream newFile("Highscores/Highscore_" + to_string(playedAtSpeed) + ".txt",ios_base::trunc);                                //truncating file

    for(auto iter =loadedHighscores.rbegin();iter!=loadedHighscores.rend();++iter){           //pre-C++11 code would be map<int,string>::reverse_iterator it=

        if(newScore > iter->first && !inserted){
            inserted = true;
            newFile << nick << " " << newScore << endl;
        }
        if (next(iter) != loadedHighscores.rend()) {                                        //skip last iteration - always just 8 best scores
            newFile << iter->second << " " << iter->first << endl;
        }
    }
}

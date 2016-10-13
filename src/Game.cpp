#include "Game.h"
#include "Menu.h"
#include "Board.h"
#include "NewHighscore.h"
#include "tinyxml2.h"
#include "tinyxml.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include<fstream>
#include <set>

Game::Game():ammunitionBox()
{
    escape=false;
    score=0;
    remainingBullets=20;
}

Game::~Game()
{
    //dtor
}

void Game::runGame(RenderWindow &window){
    Vector2i source(1,DOWN);
    Clock clock;
    set<int> generatedTimes;
    set<int> ammunitionTimes;

    ///READ CURRENT SETTINGS
    if(!this->readAndSetSettings("GameSettings.xml")){
        window.close();
    }

    ///LOAD FONT
    if(!font.loadFromFile("arial.ttf")){
        //handle error
    }

    ///player picture
    player.defineChibi();

    ///Board + background + initial view
    Board board(0,50,500);
    board.setBackground("floor.jpg",window.getSize());
    board.resetView(FloatRect(0,0,WIDTH,HEIGHT));
    board.setViewport(FloatRect(0,0,1.0f,1.0f));

    ///Enemies
    srand(time(0));   //clock for random position generator
    for(int i=0;i<enemyCount;i++){
        enemiesVector.push_back(new Enemy());
    }

    window.setKeyRepeatEnabled(true);

    while (window.isOpen() && !escape)     //main game loop
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case Event::GainedFocus:
                    cout << "Window active" << endl;
                    break;
                case Event::LostFocus:
                    cout << "Window NOT active" << endl;
                    break;
                case Event::Resized:
                    cout << "Width: " << event.size.width << "Height: " << event.size.height<< endl;
                    break;
                case Event::KeyPressed:
                    if(event.key.code == keyboard.Escape){
                        escape=true;
                        break;
                    }
                    else if(event.key.code == keyboard.Space && remainingBullets>0){      //shoot
                        bulletsVector.push_back(new Bullet(source.y,player.getPicturePosition()));
                        remainingBullets--;
                        break;
                    }
            }
        }

        ///GETTING THE DIRECTION OF MOVEMENT FROM KEYBOARD ARROWS
        if(keyboard.isKeyPressed(keyboard.Up)){
            source.y=UP;
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(0,-2));
        }
        else if(keyboard.isKeyPressed(keyboard.Down)){
            source.y=DOWN;
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(0,2));
        }
        else if(keyboard.isKeyPressed(keyboard.Right)){
            source.y=RIGHT;
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(2,0));
        }
        else if(keyboard.isKeyPressed(keyboard.Left)){
            source.y=LEFT;
            board.setFrameCounter(board.getFrameCounter()+board.getFrameSpeed()*board.restartClock());
            player.movePlayer(Vector2i(-2,0));
        }


        ///MOVE EACH ENEMY IN PLAYER DIRECTION
        for(int i=0;i<enemiesVector.size();i++){
            if(enemiesVector[i]->chasePlayer(player.getRelativePosition(),player.getPicturePosition(),enemySpeed)){        //if player caught
                this->showLosingAnimation(window,board,source);
                if(this->checkHighscore()){
                    NewHighscore nhs(enemySpeed);
                    nhs.enterName(window, font, board.getView());
                    nhs.insertNewScore(score);
                }
                escape=true;
            }
        }

        ///MOVE EACH BULLET IN ITS OWN DIRECTION
        if(bulletsVector.size()>0){
            for(int i=0;i<bulletsVector.size();i++){
                bulletsVector[i]->moveBullet();
            }
        }

        ///CHECK BULLET & ENEMY HITS
        this->checkBulletHits();


        ///INCREASE NUMBER OF ENEMIES EACH 10 SECONDS
        if(static_cast<int>(clock.getElapsedTime().asSeconds()) %10 ==0 && static_cast<int>(clock.getElapsedTime().asSeconds()) != 0 && (generatedTimes.find(static_cast<int>(clock.getElapsedTime().asSeconds())) == generatedTimes.end())){
            enemiesVector.push_back(new Enemy());               //create new pointer to new object
            generatedTimes.insert(static_cast<int>(clock.getElapsedTime().asSeconds()));            //so in 10th second only one is generated - not 15 because of all the cycles
        }


        ///CHANGE AMMUNITION PACK POSITION EACH 30 SECS
         if(static_cast<int>(clock.getElapsedTime().asSeconds()) %30 ==0 && static_cast<int>(clock.getElapsedTime().asSeconds()) != 0 && (ammunitionTimes.find(static_cast<int>(clock.getElapsedTime().asSeconds())) == ammunitionTimes.end())){
            ammunitionBox.setRandomPosition();
            ammunitionTimes.insert(static_cast<int>(clock.getElapsedTime().asSeconds()));            //so in 10th second only one is generated - not 15 because of all the cycles
        }

        ///CHECK IF PLAYER TAKES AMMUNITION BOX
        this->checkAmmunitionBox();

        ///DELETE BULLETS OUTSIDE OF VIEW
        this->checkBulletsInView(board.getView());


        ///MOVING VIEW
        board.moveViewWithPlayer(player.getRelativePosition(),Vector2u(WIDTH,HEIGHT));



        ///CHANGING CHIBI
        if(board.getFrameCounter() >=board.getSwitchFrame()){
            board.setFrameCounter(0);
            //animation...each cycle shifts displayed chibi by 64pixels to the right...if size of picture is smaller than current pixel position,
            // then go again from pixel 0.
            source.x++;
            if(source.x*64 >= player.getPlayerTexture().getSize().x){
                source.x=0;
            }
        }

        if(escape==true){       //if NewGame chosen again than reset view to the middle
                board.resetView(FloatRect(0, 0, WIDTH, HEIGHT));
        }
        window.setView(board.getView());

        sf::VertexArray line(LinesStrip, 2);
        line[0].position = player.getPicturePosition();
        line[0].color  = sf::Color::Red;
        line[1].position = ammunitionBox.getAmmunitionPicture().getPosition();
        line[1].color = sf::Color::Green;

        ///DRAW STUFF
        if(!escape){
            window.draw(board.getBackgroundRectangle());
            window.draw(ammunitionBox.getAmmunitionPicture());
            window.draw(line);
            this->drawAllMovingObjects(window,source);
            this->displayScore(window,board.getView());
            this->displayBullets(window,board.getView());
        }


        ///PRINT POSITIONS
        this->printPositions();


        window.display();
        window.clear();

    }
}

void Game::drawAllMovingObjects(RenderWindow &window,Vector2i source){
    //enemies
    for(int i=0;i<enemiesVector.size();i++){
        window.draw(enemiesVector[i]->getEnemyPicture());
    }

    //player
    player.setTexture(IntRect(source.x * 64, source.y *110, 64, 110));   //(start cropping X, start cropping Y, size in X, size in Y direction)
    window.draw(player.getPlayerImage());

    //bullets
    for(int i=0;i<bulletsVector.size();i++){
        window.draw(bulletsVector[i]->getBulletPicture());
    }
}

void Game::printPositions(){
    player.printCurrentPosition();
    for(int i=0;i<enemiesVector.size();i++){
        enemiesVector[i]->printCurrentPosition();
    }
    cout << "Number of active bullets is " << bulletsVector.size() << endl;

    for(int i=0;i<bulletsVector.size();i++){
        bulletsVector[i]->printCurrentPosition();
    }
    cout<<endl;
}

void Game::checkBulletHits(){
    for(int i=0;i<bulletsVector.size();i++){
        for(int j=0;j<enemiesVector.size();j++){
            if(bulletsVector[i]->getBulletPicture().getGlobalBounds().intersects(enemiesVector[j]->getEnemyPicture().getGlobalBounds())){   //enemy and bullet rects intersect
                delete bulletsVector[i];                            //delete object which pointer points to
                delete enemiesVector[j];
                bulletsVector.erase(bulletsVector.begin()+i);       //delete the actual pointer
                enemiesVector.erase(enemiesVector.begin()+j);
                enemiesVector.push_back(new Enemy());               //create new pointer to new object
                score++;
                break;                                              //bullet kills just one enemy, therefore I need to break from inner loop
            }
        }
    }
}


bool Game::readAndSetSettings(string filename){
    TiXmlDocument doc(filename);
    if(!doc.LoadFile()){
        cout << "Error loading settings xml" << endl;
        return false;
    }
    TiXmlElement *pRoot, *numberOfEnemiesNode,*speedNode;
    pRoot = doc.FirstChildElement("GameSettings");
    numberOfEnemiesNode = pRoot->FirstChildElement("numberOfEnemies");
    speedNode = pRoot->FirstChildElement("enemySpeed");
    if(pRoot && numberOfEnemiesNode && speedNode)
    {
        enemyCount=atoi(numberOfEnemiesNode->GetText());
        enemySpeed=atoi(speedNode->GetText());
        return true;
    }
    return false;
}

void Game::checkBulletsInView(View view){
    FloatRect viewRect(view.getCenter().x-WIDTH/2,view.getCenter().y-HEIGHT/2,WIDTH,HEIGHT);        //create rectangle of current view
    for(int i=0;i<bulletsVector.size();i++){
        if(!bulletsVector[i]->getBulletPicture().getGlobalBounds().intersects(viewRect)){           //compare view rectangle with bullet sprite bounds
            delete bulletsVector[i];
            bulletsVector.erase(bulletsVector.begin()+i);
        }
    }
}

void Game::displayScore(RenderWindow &window, View view){
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: "+to_string(score));
    scoreText.setColor(Color::White);
    scoreText.setPosition(view.getCenter().x-WIDTH/2,view.getCenter().y-HEIGHT/2);
    window.draw(scoreText);
}

void Game::displayBullets(RenderWindow &window, View view){
    Text bulletsText;
    bulletsText.setFont(font);
    bulletsText.setString("Bullets: "+to_string(remainingBullets));
    bulletsText.setColor(Color::White);
    bulletsText.setPosition(view.getCenter().x+WIDTH/2-170,view.getCenter().y-HEIGHT/2);
    window.draw(bulletsText);
}

bool Game::checkHighscore(){
    ifstream file("Highscores/Highscore_" + to_string(enemySpeed) + ".txt");
    string str;
    int readScore;
    stringstream strValue;
    while (getline(file, str))
    {
        readScore =  atoi(str.substr(str.find(" ") + 1).c_str());
        if(score>readScore){
            return true;
        }
    }
    return false;
}

void Game::showLosingAnimation(RenderWindow &window,Board &board,Vector2i source){
    Text loseText;
    loseText.setString("Got caught!");
    loseText.setColor(Color::Red);
    loseText.setFont(font);
    loseText.setRotation(-25);
    loseText.setPosition(player.getPicturePosition().x,player.getPicturePosition().y);
    int i=0;
    while(i<200){
        loseText.setCharacterSize(430-i*2);
        window.draw(board.getBackgroundRectangle());
        this->drawAllMovingObjects(window,source);
        this->displayScore(window,board.getView());
        window.draw(loseText);
        window.display();
        i++;
    }
    Time delayTime = seconds(1);
    sleep(delayTime);
}

void Game::checkAmmunitionBox(){
    if(player.getPlayerImage().getGlobalBounds().intersects(ammunitionBox.getAmmunitionPicture().getGlobalBounds())){
        remainingBullets = remainingBullets + rand() % (2*(enemySpeed+enemiesVector.size()));
        ammunitionBox.setRandomPosition();
    }
}


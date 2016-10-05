#include "Board.h"
#include <SFML/Graphics.hpp>

Board::Board()
{
    //ctor
}

Board::Board(float constFrameCounter,float constSwitchFrame, float constFrameSpeed)
{
    switchFrame=constSwitchFrame;
    frameCounter=constFrameCounter;
    frameSpeed=constFrameSpeed;
    //clock=constClock;
}

Board::~Board()
{
    //dtor
}

float Board::getFrameCounter(){
    return frameCounter;
}
float Board::getSwitchFrame(){
    return switchFrame;
}
float Board::getFrameSpeed(){
    return frameSpeed;
}
Clock Board::getClock(){
    return clock;
}
bool Board::getUpdateFrame(){
    return updateFrame;
}
void Board::setFrameCounter(float newFrameCounter){
    frameCounter=newFrameCounter;
}
void Board::setSwitchFrame(float newSwitchFrame){
    switchFrame=newSwitchFrame;
}
void Board::setFrameSpeed(float newFrameSpeed){
    frameSpeed=newFrameSpeed;
}
void Board::setClock(Clock newClock){
    clock=newClock;
}
void Board::setUpdateFrame(bool newUpdateFrame){
    updateFrame=newUpdateFrame;
}

void Board::setBackground(string picture,Vector2u wSize){
    bTexture.setSmooth(true);
    bTexture.setRepeated(true);
    if(!bTexture.loadFromFile(picture)){
        cout << "Not able to load background image" << endl;
    }

    backgroundRectangle.setSize(Vector2f(wSize.x*2*10,wSize.y*2*10));     //2times bigger than screen...*10 because of scale
    backgroundRectangle.scale(Vector2f(0.1,0.1));
    int xBackgroundShift = wSize.x/2;        //dont know why but value needs to be saved in variable first
    int yBackgroundShift = wSize.y/2;
    backgroundRectangle.setPosition(-xBackgroundShift,-yBackgroundShift);
    backgroundRectangle.setOutlineColor(Color::Blue);
    backgroundRectangle.setOutlineThickness(50.0f);
    backgroundRectangle.setTexture(&bTexture);
    backgroundRectangle.setTextureRect(IntRect(0,0,wSize.x*2*10,wSize.y*2*10));
}

void Board::resetView(FloatRect rect){
    view.reset(rect);
}

void Board::setViewport(FloatRect rect){
    view.setViewport(rect);
}

float Board::restartClock(){
    return clock.restart().asSeconds();
}

View Board::getView(){
    return view;
}

RectangleShape Board::getBackgroundRectangle(){
    return backgroundRectangle;
}

void Board::moveViewWithPlayer(Vector2i playerPosition, Vector2u wSize){
    int xBorder=WIDTH_VIEW_BORDER;      //no idea why using defined macro doesn't work directly
    int yBorder=HEIGHT_VIEW_BORDER;

    if(playerPosition.x < -xBorder){
        if(playerPosition.y>yBorder || playerPosition.y<-yBorder){}
        else{
            resetView(FloatRect(-xBorder,playerPosition.y,wSize.x,wSize.y));
        }
    }
    else if(playerPosition.x>xBorder)
        if(playerPosition.y>yBorder || playerPosition.y<-yBorder){}
        else{
            resetView(FloatRect(xBorder,playerPosition.y,wSize.x,wSize.y));
        }
    else if(playerPosition.y>yBorder)
        resetView(FloatRect(playerPosition.x,yBorder,wSize.x,wSize.y));
    else if(playerPosition.y<-yBorder)
        resetView(FloatRect(playerPosition.x,-yBorder,wSize.x,wSize.y));
    else{
        resetView(FloatRect(playerPosition.x,playerPosition.y,wSize.x,wSize.y));
    }
}

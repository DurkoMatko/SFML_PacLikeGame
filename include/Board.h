#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define HEIGHT 800
#define WIDTH 1200
#define WIDTH_VIEW_BORDER WIDTH/2+4
#define HEIGHT_VIEW_BORDER HEIGHT/2+6
#define X_MOVEMENT_LIMIT WIDTH-22
#define Y_MOVEMENT_LIMIT HEIGHT-21

using namespace std;
using namespace sf;


class Board
{
    public:
        Board();
        Board(float constFrameCounter,float constSwitchFrame, float constFrameSpeed);
        virtual ~Board();
        float getFrameCounter();
        float getSwitchFrame();
        float getFrameSpeed();
        Clock getClock();
        View getView();
        RectangleShape getBackgroundRectangle();
        bool getUpdateFrame();
        void setFrameCounter(float newFrameCounter);
        void setSwitchFrame(float newSwitchFrame);
        void setFrameSpeed(float newFrameSpeed);
        void setClock(Clock newClock);
        float restartClock();
        void setUpdateFrame(bool newUpdateFrame);
        void setBackground(string picture,Vector2u wSize);
        void resetView(FloatRect rect);
        void setViewport(FloatRect rect);
        void moveViewWithPlayer(Vector2i playerPosition,Vector2u wSize);

    protected:
    private:
        float frameCounter;
        float switchFrame;
        float frameSpeed;
        Clock clock;
        bool updateFrame;
        Texture bTexture;
        RectangleShape backgroundRectangle;
        View view;
};

#endif // BOARD_H

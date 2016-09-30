#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#ifndef PLAYERCHIBI_H
#define PLAYERCHIBI_H


using namespace sf;
using namespace std;

class PlayerChibi
{
    public:
        PlayerChibi();
        virtual ~PlayerChibi();
        void defineChibi(String picture,Vector2u wSize);
        Vector2i getPosition();
        void setPosition(Vector2i newPosition);
        void movePlayer(Vector2i change);
        void setTexture(IntRect pictureRectangle);
        Sprite getPlayerImage();
        Texture getPlayerTexture();
        Vector2f getPicturePosition();
        void printCurrentPosition();

    protected:
    private:
        Vector2i relativePosition;
        Texture pTexture;
        Sprite playerImage;
};

#endif // PLAYERCHIBI_H

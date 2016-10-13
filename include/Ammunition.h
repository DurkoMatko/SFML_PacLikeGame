#ifndef AMMUNITION_H
#define AMMUNITION_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Ammunition
{
    public:
        Ammunition();
        virtual ~Ammunition();
        Sprite getAmmunitionPicture();
        Vector2f setRandomPosition();
    protected:
    private:
        Texture aTexture;
        Sprite ammunitionImage;
};

#endif // AMMUNITION_H

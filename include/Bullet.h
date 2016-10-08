#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
    public:
        Bullet();
        Bullet(int direction,Vector2f playerPicturePosition);
        virtual ~Bullet();
        Sprite getBulletPicture();
        void moveBullet();
    protected:
    private:
        Vector2f directionVector;
        Texture bTexture;
        Sprite bulletImage;
};

#endif // BULLET_H
